#include <Windows.h>
#include <thread>
#include <iostream>

#include <math/math.h>
#include <instance/instance.h>
#include <hook/hook.hpp>
#include <render/render.h>

void debug_console()
{
    FILE* f;
    DWORD old;
    VirtualProtect(&FreeConsole, 1, PAGE_EXECUTE_READWRITE, &old);
    *reinterpret_cast<byte*>(&FreeConsole) = 0xC3; // return opcode
    VirtualProtect(&FreeConsole, 1, old, &old);

    AllocConsole();
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONOUT$", "w", stderr);
    freopen_s(&f, "CONIN$", "r", stdin);

    SetConsoleTitleA("RobloxESP - debug");
}

void mainthread()
{
    debug_console();

    render::init();

    /*
    visual_engine_t* visual_engine = get_visual_engine();

    std::printf("Visual Engine: 0x%08X\n", visual_engine);
    std::printf("Frames elapsed: %zu\n", visual_engine->frames_passed);

    instance_t datamodel = scheduler_t::get().get_datamodel();

    std::printf("datamodel: 0x%08X\n", datamodel.get_pointer());

    std::printf("screen dimensions: %d x %d\n", static_cast<int>(visual_engine->screen_x), static_cast<int>(visual_engine->screen_y));

    HDC dev_context = GetDC(FindWindowW(NULL, L"Roblox"));
    SelectObject(dev_context, GetStockObject(DC_PEN));
    SetDCPenColor(dev_context, RGB(255, 0, 255));

    while (true)
    {
        if (std::optional<instance_t> players = datamodel.get_child_by_class("Players"))
        {
            for (instance_t& player : players->get_children())
            {
                if (instance_t character{ *reinterpret_cast<std::uintptr_t*>(player.get_pointer() + 0x7C) }; character.is_valid())
                {
                    if (std::optional<instance_t> head = character.get_child_by_name("Head"))
                    {
                        Vector3_t* position = (*reinterpret_cast<Vector3_t*(__thiscall**)(std::uintptr_t)>(*reinterpret_cast<std::uintptr_t*>(head->get_pointer()) + 0xF8))(head->get_pointer());
                        std::printf("%s position: (%f, %f, %f)\n", player.get_name().c_str(), position->x, position->y, position->z);
                    }
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
    */
}




BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        std::thread(mainthread).detach();
    return TRUE;
}