#include "api/include/lstring.h"
#include "api/include/ltable.h"


std::uint32_t fishS_hash(const char* str, std::size_t len)
{
    // Note that this hashing algorithm is replicated in BytecodeBuilder.cpp, BytecodeBuilder::getStringHash
    unsigned int a = 0, b = 0;
    unsigned int h = unsigned(len);

    // hash prefix in 12b chunks (using aligned reads) with ARX based hash (LuaJIT v2.1, lookup3)
    // note that we stop at length<32 to maintain compatibility with Lua 5.1
    while (len >= 32)
    {
#define rol(x, s) ((x >> s) | (x << (32 - s)))
#define mix(u, v, w) a ^= h, a -= rol(h, u), b ^= a, b -= rol(a, v), h ^= b, h -= rol(b, w)

        // should compile into fast unaligned reads
        std::uint32_t block[3];
        memcpy(block, str, 12);

        a += block[0];
        b += block[1];
        h += block[2];
        mix(14, 11, 25);
        str += 12;
        len -= 12;

#undef mix
#undef rol
    }

    // original Lua 5.1 hash for compatibility (exact match when len<32)
    for (size_t i = len; i > 0; --i)
        h ^= (h << 5) + (h >> 2) + (uint8_t)str[i - 1];

    return h;
}

std::uintptr_t fishS_newlstr(std::uintptr_t rL, const char* str, std::size_t len)
{
    using namespace offsets::global;

    std::uint32_t h = fishS_hash(str, len);
    std::uintptr_t gs = get_encrypted(rL + offsets::lua_state::global, encryption::lua_state::global);

    std::uintptr_t el = *reinterpret_cast<std::uintptr_t*>(*reinterpret_cast<std::uint32_t*>(gs + string_table::hash) + 4 * fish_lmod(h, *reinterpret_cast<std::size_t*>(gs + string_table::size)));

    for (el; el != NULL; el = *reinterpret_cast<std::uint32_t*>(el + offsets::string::next))
    {
        if (get_encrypted(el + offsets::string::len, encryption::string::len) == len && !memcmp(str, reinterpret_cast<const char*>(el + offsets::string::data), len))
            return el;
    }

    return 0;
}


#include <iostream>
void fish_dumpallstrings(std::uintptr_t rL) // just a fun test project, works flawlessly
{
    using namespace offsets::global;

    std::uintptr_t gs = get_encrypted(rL + offsets::lua_state::global, encryption::lua_state::global);
    std::uintptr_t hash_start = *reinterpret_cast<std::uint32_t*>(gs + string_table::hash);

    for (std::size_t i = 0; i < *reinterpret_cast<std::size_t*>(gs + string_table::size); ++i)
    {
        std::uintptr_t ts = *reinterpret_cast<std::uintptr_t*>(hash_start + (4 * i));
        if (ts)
        {
            std::string str{ reinterpret_cast<const char*>(ts + offsets::string::data), get_encrypted(ts + offsets::string::len, encryption::string::len) };
            std::printf("0x%p: \"%s\"\n", ts, str.c_str());
        }
    }
}