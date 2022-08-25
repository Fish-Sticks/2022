#pragma once
#include <Windows.h>
#include <cstdint>

//			ADDRESSES
const std::uintptr_t base = reinterpret_cast<std::uintptr_t>(GetModuleHandle(NULL));



//			RETCHECK BYPASS
const std::uintptr_t rbx_retcheck_addy = base + 0x00A3DCD7;

namespace retcheck_
{
	static void __declspec(noinline) __declspec(naked) stub()
	{
		__asm
		{
			pop edi
			push rbx_retcheck_addy
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
	retcheck(auto addy) : addy{ *reinterpret_cast<std::uintptr_t*>(&addy) } {}

	template <typename... args>
	__declspec(noinline) auto operator()(args... a)
	{
		std::uintptr_t addy = this->addy;
		__asm mov eax, addy // *sigh*
		return reinterpret_cast<T>(retcheck_::stub)(a...);
	}
};




const double xor_const_addy = *reinterpret_cast<double*>(base + 0x01633870);

const std::uintptr_t rbx_getscheduler_addy = base + 0x000DF320;
const std::uintptr_t rbx_get_lua_state_addy = base + 0x001287C0;

const std::uintptr_t rbx_getfield_addy = base + 0x00145890;
const std::uintptr_t rbx_setfield_addy = base + 0x001473F0;
const std::uintptr_t rbx_pcall_addy = base + 0x00146580;
const std::uintptr_t rbx_pushnumber_addy = base + 0x00146A60;
const std::uintptr_t rbx_pushlstring_addy = base + 0x00146960;

const std::uintptr_t rbx_typename_addy = base + 0x00147E10;
const std::uintptr_t rbx_newthread_addy = base + 0x00146280;
const std::uintptr_t rbx_lual_ref_addy = base + 0x00141B10;

const std::uintptr_t rbx_luas_newlstr_addy = base + 0x00142520;
const std::uintptr_t rbx_luav_gettable_addy = base + 0x00144B50;
const std::uintptr_t rbx_luav_settable_addy = base + 0x00144D90;

const std::uintptr_t rbx_luad_precall_addy = base + 0x0013F6D0;

const std::uintptr_t rbx_luad_reallocstack_addy = base + 0x0013FAB0;
const std::uintptr_t rbx_adjust_varargs_addy = base + 0x0013B980;

//			DECLARATIONS
using rbx_getscheduler_t = std::uintptr_t(__cdecl*)();
using rbx_get_lua_state_t = std::uintptr_t(__thiscall*)(std::uintptr_t script_context, int security_context);

using rbx_getfield_t = void(__cdecl*)(std::uintptr_t rl, int idx, const char* name);
using rbx_pcall_t = int(__cdecl*)(std::uintptr_t rl, int nargs, int nres, int nerr);
using rbx_pushnumber_t = void(__cdecl*)(std::uintptr_t rl, double num);
using rbx_pushstring_t = void(__cdecl*)(std::uintptr_t rl, const char* str, size_t len);
using rbx_typename_t = const char* (__cdecl*)(std::uintptr_t rL, int tt);
using rbx_lual_ref_t = int(__cdecl*)(std::uintptr_t rL, int idx);
using rbx_newthread_t = std::uintptr_t(__cdecl*)(std::uintptr_t rL);

using rbx_luas_newlstr_t = std::uintptr_t(__cdecl*)(std::uintptr_t rL, const char* str, size_t len);
using rbx_luav_gettable_t = void(__cdecl*)(std::uintptr_t rL, std::uintptr_t* table, std::uintptr_t* key, std::uintptr_t* out);

using rbx_luad_precall_t = int(__cdecl*)(std::uintptr_t rL, std::uintptr_t* func, int results);
using rbx_luad_reallocstack_t = void(__cdecl*)(std::uintptr_t rL, int stack);
using rbx_adjust_varargs_t = int(__cdecl*)(std::uintptr_t rL, std::uintptr_t proto, int vals);


//			DEFINITIONS
static retcheck<rbx_getfield_t> rbx_getfield = retcheck<rbx_getfield_t>(rbx_getfield_addy);
static retcheck<rbx_getfield_t> rbx_setfield = retcheck<rbx_getfield_t>(rbx_setfield_addy);
static retcheck<rbx_pcall_t> rbx_pcall = retcheck<rbx_pcall_t>(rbx_pcall_addy);
static retcheck<rbx_pushnumber_t> rbx_pushnumber = retcheck<rbx_pushnumber_t>(rbx_pushnumber_addy);
static retcheck<rbx_pushstring_t> rbx_pushlstring = retcheck<rbx_pushstring_t>(rbx_pushlstring_addy);
static retcheck<rbx_luad_precall_t> rbx_luad_precall = retcheck<rbx_luad_precall_t>(rbx_luad_precall_addy);
static retcheck<rbx_lual_ref_t> rbx_lual_ref = retcheck<rbx_lual_ref_t>(rbx_lual_ref_addy);
static retcheck<rbx_newthread_t> rbx_newthread = retcheck<rbx_newthread_t>(rbx_newthread_addy);

static rbx_get_lua_state_t rbx_get_lua_state = reinterpret_cast<rbx_get_lua_state_t>(rbx_get_lua_state_addy);
static rbx_getscheduler_t rbx_getscheduler = reinterpret_cast<rbx_getscheduler_t>(rbx_getscheduler_addy);
static rbx_typename_t rbx_typename = reinterpret_cast<rbx_typename_t>(rbx_typename_addy);


static rbx_luas_newlstr_t rbx_luas_newlstr = reinterpret_cast<rbx_luas_newlstr_t>(rbx_luas_newlstr_addy);
static rbx_luav_gettable_t rbx_luav_gettable = reinterpret_cast<rbx_luav_gettable_t>(rbx_luav_gettable_addy);
static rbx_luav_gettable_t rbx_luav_settable = reinterpret_cast<rbx_luav_gettable_t>(rbx_luav_settable_addy);
static rbx_luad_reallocstack_t rbx_luad_reallocstack = reinterpret_cast<rbx_luad_reallocstack_t>(rbx_luad_reallocstack_addy);
static rbx_adjust_varargs_t rbx_adjust_varargs = reinterpret_cast<rbx_adjust_varargs_t>(rbx_adjust_varargs_addy);

#define rbx_pushstring(rl, str) rbx_pushlstring(rl, str, strlen(str))
#define rbx_getglobal(rl, str) rbx_getfield(rl, -10002, str)


namespace offsets
{
	namespace scheduler
	{
		constexpr std::uint32_t job_start = 0x220;
		constexpr std::uint32_t job_end = 0x224;
	}

	namespace job
	{
		constexpr std::uint32_t name = 0x54;
	}

	namespace waiting_scripts_job
	{
		constexpr std::uint32_t script_context = 0x240;
	}

	namespace lua_state
	{
		constexpr std::uint32_t top = 0x10;
		constexpr std::uint32_t base = 0x1C;
		constexpr std::uint32_t gt = 0x68;

		constexpr std::uint32_t ci = 12;
		constexpr std::uint32_t ci_top = 8;

		constexpr std::uint32_t errfunc = 0x60;
		constexpr std::uint32_t stack_last = 0x20;
		constexpr std::uint32_t stacksize = 0x30;
	}
}