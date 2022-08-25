#include <Windows.h>
#include "addresses.hpp"
#include "declarations.hpp"

fish_getscheduler_t fish_getscheduler;
fish_getstate_t fish_getstate;
retcheck<fish_deserialize_t> fish_deserialize;
retcheck<fish_spawn_t> fish_spawn;
fish_index2adr_t fish_index2adr;
fishG_runerror_t fishG_runerror;
fishC_barriertable_t fishC_barriertable;

namespace addresses // C++ defined
{
	std::uintptr_t fish_retcheck_addy = addresses::fish_retcheck_addy_;
	std::uintptr_t fishO_nilobject = addresses::fishO_nilobject_;
}

__declspec(noinline) void make_defs()
{
	std::uintptr_t base = reinterpret_cast<std::uintptr_t>(GetModuleHandle(NULL));

	addresses::fish_retcheck_addy += base;
	addresses::fishO_nilobject += base;

	fish_getscheduler = reinterpret_cast<fish_getscheduler_t>(base + addresses::fish_getscheduler);
	fish_getstate = reinterpret_cast<fish_getstate_t>(base + addresses::fish_getstate);
	fish_deserialize = retcheck<fish_deserialize_t>(base + addresses::fish_deserializer);
	fish_spawn = retcheck<fish_spawn_t>(base + addresses::fish_spawn);
	fish_index2adr = reinterpret_cast<fish_index2adr_t>(base + addresses::fish_index2adr);
	fishG_runerror = reinterpret_cast<fishG_runerror_t>(base + addresses::fishG_runerror);
	fishC_barriertable = reinterpret_cast<fishC_barriertable_t>(base + addresses::fishC_barriertable);
}