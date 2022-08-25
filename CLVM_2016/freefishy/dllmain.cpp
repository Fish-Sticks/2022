#include <Windows.h>
#include <thread>
#include <iostream>
#include <stack>

#include "src/addresses.hpp"
#include "src/scheduler/scheduler.hpp"
#include "src/execution/execution.h"

void make_console()
{
    DWORD old;
    AllocConsole();
    VirtualProtect(&FreeConsole, 1, PAGE_EXECUTE_READWRITE, &old);
    *reinterpret_cast<byte*>(&FreeConsole) = 0xC3;
    VirtualProtect(&FreeConsole, 1, old, &old);

    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONIN$", "r", stdin);

    SetConsoleTitleA("freefishy.exe");
}

std::stack<std::string> script_queue{};
std::uintptr_t g_waiting_scripts_job = 0;

void run_lua_script()
{
    std::uintptr_t script_context = *reinterpret_cast<std::uintptr_t*>(g_waiting_scripts_job + offsets::waiting_scripts_job::script_context);
    std::uintptr_t rL = rbx_get_lua_state(script_context, 0);

    static bool ran_luac = false;
    if (!ran_luac)
    {
        ran_luac = true;

        rbx_getglobal(rL, "game");
        rbx_getfield(rL, -1, "Workspace");
        rbx_getglobal(rL, "warn");
        rbx_pushstring(rL, "Filtering status:");
        rbx_getfield(rL, -3, "FilteringEnabled");
        rbx_pcall(rL, 2, 0, 0);

        *reinterpret_cast<int*>(rL + offsets::lua_state::top) = *reinterpret_cast<int*>(rL + offsets::lua_state::base);
    }

    static execution_t execution{ rL };

    while (!script_queue.empty())
    {
        std::printf("Running script!\n");

        std::string& script = script_queue.top();
        execution.run_script(script, "Testing");

        script_queue.pop();
    }
}


std::uintptr_t orig_func = 0;
int __stdcall waiting_scripts_job_hook(int a, int b)
{
    run_lua_script();
    return reinterpret_cast<int(__stdcall*)(int a, int b)>(orig_func)(a, b);
}


LONG UEF(_EXCEPTION_POINTERS* ExceptionInfo)
{
    std::printf("Exception at 0x%08X\n", ExceptionInfo->ExceptionRecord->ExceptionAddress);
    std::printf("Exception code: 0x%08X\n", ExceptionInfo->ExceptionRecord->ExceptionCode);

    std::printf("Registers:\neax: 0x%08X\nebx: 0x%08X\necx: 0x%08X\nedx: 0x%08X\nedi: 0x%08X\n",
        ExceptionInfo->ContextRecord->Eax, ExceptionInfo->ContextRecord->Ebx, ExceptionInfo->ContextRecord->Ecx, ExceptionInfo->ContextRecord->Edx, ExceptionInfo->ContextRecord->Edi);

    std::uintptr_t ebp = ExceptionInfo->ContextRecord->Ebp;
    for (int i = 0; i < 5; ++i)
    {
        std::printf("call stack [%d]: 0x%08X\n", i, *reinterpret_cast<std::uintptr_t*>(ebp + 4));
        ebp = *reinterpret_cast<std::uintptr_t*>(ebp);
    }

    std::cin.get();

    return EXCEPTION_CONTINUE_EXECUTION;
}

void setup_exceptions()
{
    using unhandled_shit_t = LPTOP_LEVEL_EXCEPTION_FILTER(WINAPI*)(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter);

    HMODULE h_kernelbase = GetModuleHandleA("KERNELBASE.dll");

    unhandled_shit_t SetUnhandledExceptionFilter_safe = reinterpret_cast<unhandled_shit_t>(GetProcAddress(h_kernelbase, "SetUnhandledExceptionFilter"));

    SetUnhandledExceptionFilter_safe(reinterpret_cast<LPTOP_LEVEL_EXCEPTION_FILTER>(&UEF));

    CloseHandle(h_kernelbase);
}

void main_thread()
{
    make_console();
    scheduler_t task_scheduler{};

    setup_exceptions();

    for (int i = 0; i < 10; ++i)
    {
        std::printf("%d - %s\n", i, rbx_typename(NULL, i));
    }

    if (const auto waiting_scripts_job = task_scheduler.get_job_by_name("WaitingScriptJob"))
    {
        std::printf("WaitingScriptsJob: 0x%08X\n", waiting_scripts_job.value());
        g_waiting_scripts_job = waiting_scripts_job.value();
        orig_func = task_scheduler.hook_job_vtable(waiting_scripts_job.value(), &waiting_scripts_job_hook);

        std::string input{};
        while (std::getline(std::cin, input))
        {
            script_queue.push(input);
        }
    }
    else
        std::printf("Failed to find WaitingScriptsJob!\n");
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

