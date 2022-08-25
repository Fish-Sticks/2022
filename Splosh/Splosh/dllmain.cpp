#include <Windows.h>
#include <thread>

#include "src/addresses/declarations.hpp"
#include "src/console/include/console.h"
#include "src/execution/include/execution.h"
#include "src/scheduler/include/scheduler.h"

#include "src/api/include/lstring.h"

const scheduler_t scheduler{};
const execution_t execution{&scheduler};

/*
 * Luau heap uses a size-segregated page structure, with individual pages and large allocations
 * allocated using system heap (via frealloc callback).
 *
 * frealloc callback serves as a general, if slow, allocation callback that can allocate, free or
 * resize allocations:
 *
 *    void* frealloc(void* ud, void* ptr, size_t oldsize, size_t newsize);
 *
 * frealloc(ud, NULL, 0, x) creates a new block of size x
 * frealloc(ud, p, x, 0) frees the block p (must return NULL)
 * frealloc(ud, NULL, 0, 0) does nothing, equivalent to free(NULL)
 *
 * frealloc returns NULL if it cannot create or reallocate the area  
 * (any reallocation to an equal or smaller size cannot fail!)
 *
 * On top of this, Luau implements heap storage which is split into two types of allocations:
 *
 * - GCO, short for "garbage collected objects"
 * - other objects (for example, arrays stored inside table objects)
 *
 * The heap layout for these two allocation types is a bit different.
 *
 * All GCO are allocated in pages, which is a block of memory of ~16K in size that has a page header
 * (lua_Page). Each page contains 1..N blocks of the same size, where N is selected to fill the page
 * completely. This amortizes the allocation cost and increases locality. Each GCO block starts with
 * the GC header (GCheader) which contains the object type, mark bits and other GC metadata. If the
 * GCO block is free (not used), then it must have the type set to TNIL; in this case the block can
 * be part of the per-page free list, the link for that list is stored after the header (freegcolink).
 *
 * Importantly, the GCO block doesn't have any back references to the page it's allocated in, so it's
 * impossible to free it in isolation - GCO blocks are freed by sweeping the pages they belong to,
 * using luaM_freegco which must specify the page; this is called by page sweeper that traverses the
 * entire page's worth of objects. For this reason it's also important that freed GCO blocks keep the
 * GC header intact and accessible (with type = NIL) so that the sweeper can access it.
 *
 * Some GCOs are too large to fit in a 16K page without excessive fragmentation (the size threshold is
 * currently 512 bytes); in this case, we allocate a dedicated small page with just a single block's worth
 * storage space, but that requires allocating an extra page header. In effect large GCOs are a little bit
 * less memory efficient, but this allows us to uniformly sweep small and large GCOs using page lists.
 *
 * All GCO pages are linked in a large intrusive linked list (global_State::allgcopages). Additionally, 
 * for each block size there's a page free list that contains pages that have at least one free block
 * (global_State::freegcopages). This free list is used to make sure object allocation is O(1).
 *
 * Compared to GCOs, regular allocations have two important differences: they can be freed in isolation,
 * and they don't start with a GC header. Because of this, each allocation is prefixed with block metadata,
 * which contains the pointer to the page for allocated blocks, and the pointer to the next free block
 * inside the page for freed blocks.
 * For regular allocations that are too large to fit in a page (using the same threshold of 512 bytes),
 * we don't allocate a separate page, instead simply using frealloc to allocate a vanilla block of memory.
 *
 * Just like GCO pages, we store a page free list (global_State::freepages) that allows O(1) allocation;
 * there is no global list for non-GCO pages since we never need to traverse them directly.
 *
 * In both cases, we pick the page by computing the size class from the block size which rounds the block
 * size up to reduce the chance that we'll allocate pages that have very few allocated blocks. The size
 * class strategy is determined by SizeClassConfig constructor.
 *
 * Note that when the last block in a page is freed, we immediately free the page with frealloc - the
 * memory manager doesn't currently attempt to keep unused memory around. This can result in excessive
 * allocation traffic and can be mitigated by adding a page cache in the future.
 *
 * For both GCO and non-GCO pages, the per-page block allocation combines bump pointer style allocation
 * (lua_Page::freeNext) and per-page free list (lua_Page::freeList). We use the bump allocator to allocate
 * the contents of the page, and the free list for further reuse; this allows shorter page setup times
 * which results in less variance between allocation cost, as well as tighter sweep bounds for newly
 * allocated pages.
 */

void type_dumper()
{
    std::uintptr_t type_array = reinterpret_cast<std::uintptr_t>(GetModuleHandle(NULL)) + 0x218C1D8;

    std::printf("enum fish_type\n{\n");
    std::printf("fish_TNONE = -1,\n");
    for (std::int32_t i = 0; i < 10; ++i)
    {
        std::string type_name = *(reinterpret_cast<const char**>(type_array) + i);
        std::transform(type_name.begin(), type_name.end(), type_name.begin(), toupper);
        std::printf((std::string("fish_T") + type_name + ",\n").c_str());
    }
    std::printf("};\n");
}

void main_thread()
{
    make_console("Splosh | The reverse engineers relapse.");
    make_defs(); // always call this first, it bases all the addresses ; makes them BASED

    scheduler.begin();

    scheduler.print_jobs();
    execution.hook_waiting_scripts_job();

    type_dumper();

    std::uintptr_t rL = scheduler.get_global_luastate();

    std::string input;
    while (std::getline(std::cin, input))
    {
        execution.run_script(input);
    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        std::thread(main_thread).detach();
        break;
    }
    return TRUE;
}