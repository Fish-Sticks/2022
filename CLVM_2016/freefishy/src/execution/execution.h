#pragma once
#include <Windows.h>
#include <string>
#include <iostream>

extern "C"
{
#include "lua/lua.h"
#include "lua/lapi.h"
#include "lua/lstate.h"
#include "lua/lopcodes.h"
#include "lua/lfunc.h"
#include "lua/lobject.h"
#include "lua/lauxlib.h"
#include "lua/ldebug.h"
#include "lua/ldo.h"
#include "lua/lgc.h"
#include "lua/lmem.h"
#include "lua/lstring.h"
#include "lua/ltable.h"
#include "lua/ltm.h"
#include "lua/lundump.h"
#include "lua/lvm.h"
}

class execution_t
{
private:
	std::uintptr_t r_L;
	lua_State* g_L;

	execution_t(const execution_t&) = delete;
public:
	explicit execution_t(std::uintptr_t rL);
	void run_script(const std::string& script, const std::string& script_name);
};