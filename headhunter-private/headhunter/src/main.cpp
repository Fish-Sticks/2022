#include <Windows.h>
#include <thread>

#include "console/console.h"
#include "scheduler/scheduler.h"
#include "execution/execution.h"
#include "communication/communication.h"
#include "api/api.h"
#include "functions/functions.h"

const console_t output{ "headhunter - fishy" };
const scheduler_t scheduler{};
const execution_t execution{ &scheduler };
const communication_t communication{};

std::unordered_map<std::string, int> ttypes;
std::unordered_map<std::string, int> ttms;

void mainfunc()
{

    output << console_t::color::cyan << "Welcome to headhunter! A not-so-simple exploit made by fishy.\nThis is the worlds first level 11!\n";
    output << console_t::color::white << "Current scheduler: 0x" << scheduler.get() << "\n";

    scheduler.print_jobs();

    output << console_t::color::pink << "Got Datamodel: 0x" << scheduler.get_datamodel() << "\n";
    output << console_t::color::pink << "Got ScriptContext: 0x" << scheduler.get_script_context() << "\n";
    output << console_t::color::pink << "Got luastate: 0x" << scheduler.get_global_luastate() << "\n";

    execution.hook_waiting_scripts_job();
    execution.set_identity(11);

    output << console_t::color::pink << "Successfully set identity to 11!\n";

    map_ttypes();

    while (true)
    {
        execution.run_script(communication.read_pipe());
    }
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        std::thread(mainfunc).detach();
        break;
    }
    return TRUE;
}