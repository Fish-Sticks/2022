#pragma once
#include <cstddef>
#include <cstdint>

#include "addresses.hpp"
#include "api/include/structs.h"

namespace retcheck_
{
	static void __declspec(noinline) __declspec(naked) stub()
	{
		__asm
		{
			pop edi
			push addresses::fish_retcheck_addy
			jmp eax
		}
	}
}

template <typename T>
class retcheck
{
private:
	std::uintptr_t addy = 0;
public:
	retcheck() {}
	retcheck(auto addy) : addy{ *reinterpret_cast<std::uintptr_t*>(&addy) } {}

	template <typename... args>
	__declspec(noinline) auto operator()(args... a)
	{
		std::uintptr_t addy = this->addy;
		__asm mov eax, addy // *sigh*
		return reinterpret_cast<T>(retcheck_::stub)(a...);
	}
};

using fish_getscheduler_t = std::uintptr_t(__cdecl*)();
extern fish_getscheduler_t fish_getscheduler;

using fish_getstate_t = std::uintptr_t(__thiscall*)(std::uintptr_t script_context, std::int32_t* state_index);
extern fish_getstate_t fish_getstate;

using fish_deserialize_t = std::int32_t(__fastcall*)(std::uintptr_t rL, const char* chunk_name, const char* bytecode, std::size_t length, std::int32_t custom_environment_index);
extern retcheck<fish_deserialize_t> fish_deserialize;

using fish_spawn_t = std::int32_t(__cdecl*)(std::uintptr_t rL);
extern retcheck<fish_spawn_t> fish_spawn;

using fish_index2adr_t = FishValue*(__fastcall*)(std::uintptr_t rL, std::int32_t idx);
extern fish_index2adr_t fish_index2adr;

using fishG_runerror_t = void(__cdecl*)(std::uintptr_t rL, const char* msg, ...);
extern fishG_runerror_t fishG_runerror;

using fishC_barriertable_t = void(__fastcall*)(std::uintptr_t rL, std::uintptr_t t, std::uintptr_t v);
extern fishC_barriertable_t fishC_barriertable;

extern void make_defs();