#include "execution/include/execution.h"

#include "addresses/declarations.hpp"
#include "api/include/util.h"

#include <stack>
#include <mutex>


std::mutex mutex;
std::stack<std::string> script_queue;
std::uintptr_t original_func;

std::uint8_t roblox_encoder_t::encodeOp(const std::uint8_t opcode)
{
	return opcode * 227;
}

int __fastcall scheduler_cycle(std::uintptr_t waiting_scripts_job, int fakearg, int a2)
{
	std::unique_lock<std::mutex> guard{ mutex };
	std::uintptr_t rl = execution.scheduler->get_global_luastate();

	if (!script_queue.empty())
	{
		const std::string bytecode = script_queue.top();
		script_queue.pop();
		guard.unlock();

		execution.register_globals();

		if (bytecode.at(0) == 0)
		{
			const char* msg = bytecode.c_str() + 1;
			MessageBoxA(NULL, msg, "Script Error", NULL);
		}
		else
		{
			std::printf("Running script!\n");
			fish_deserialize(rl, "splosh.exe", bytecode.c_str(), bytecode.size(), NULL);
			fish_spawn(rl);
			fish_decrement_top(rl, 1);
		}
	}

	return reinterpret_cast<int(__thiscall*)(std::uintptr_t, int)>(original_func)(waiting_scripts_job, a2);
}

void execution_t::hook_waiting_scripts_job() const
{
	this->scheduler->hook_waiting_scripts_job(scheduler_cycle, original_func);
}

void execution_t::run_script(const std::string& script) const
{
	roblox_encoder_t roblox_encoder{};
	const std::string& compiled = Luau::compile(script, {}, {}, &roblox_encoder); // no clone here, is gonna be cloned on queue
	std::unique_lock<std::mutex> guard{ mutex };
	script_queue.push(compiled);
}

void execution_t::run_bytecode(const std::string& bytecode) const
{
	std::unique_lock<std::mutex> guard{ mutex };
	script_queue.push(bytecode);
}

void execution_t::set_identity(std::int8_t identity) const
{
	std::printf("set_identity is not implemented!\n");
}

#include "api/include/api.h"
#include "api/include/lstring.h"

void execution_t::register_globals() const // make sure they get registered on the scheduler, maintain that 100% stability rate ;)
{
	static bool registered = false;
	if (!registered)
	{
		registered = true;
		std::uintptr_t rL = this->scheduler->get_global_luastate();

		fish_dumpallstrings(rL);
/*
		RL rbx_state{ rL };

		rbx_state.push_string("game");

		std::printf("string pushed!\n");

		// rbx_state.set_global("printidentity");

*/
	}
}

std::uintptr_t execution_t::get_global_state() const
{
	return this->scheduler->get_global_luastate();
}

void execution_t::set_fps(double fps) const
{
	this->scheduler->set_fps(fps);
}

execution_t::execution_t() {};

execution_t::execution_t(const scheduler_t* scheduler)
	: scheduler(scheduler) {};