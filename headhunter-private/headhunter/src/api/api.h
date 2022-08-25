#pragma once
#include <Windows.h>
#include <cstdint>

#include "addresses/addresses.hpp"

extern void rbx_spawn(std::uintptr_t rl);
extern void rbx_deserialize(std::uintptr_t rl, const char* chunk_name, const char* bytecode, int byte_len);
extern void rbx_increment_top(std::uintptr_t rl, std::int32_t amount);
extern void rbx_decrement_top(std::uintptr_t rl, std::int32_t amount);
extern void rbx_setidentity(std::uintptr_t rl, std::int8_t identity);
extern void rbx_pushcclosure(std::uintptr_t rl, void* closure);

extern void rbx_pushnumber(std::uintptr_t rl, double num);
extern void rbx_pushboolean(std::uintptr_t rl, bool b);
extern void rbx_pushstring(std::uintptr_t rl, const std::string& str);

extern double rbx_tonumber(std::uintptr_t rl, std::int32_t idx);
extern bool rbx_toboolean(std::uintptr_t rl, std::int32_t idx);
extern const char* rbx_tostring(std::uintptr_t rl, std::int32_t idx);

extern void rbx_getfield(std::uintptr_t rl, int idx, const char* k);
#define rbx_getglobal(rl, k) rbx_getfield(rl, -10002, k)

extern void rbx_setfield(std::uintptr_t rl, int idx, const char* k);
#define rbx_setglobal(rl, k) rbx_setfield(rl, -10002, k)

extern std::uintptr_t rbx_luas_newlstr(std::uintptr_t rl, const char* str, size_t len);

extern rbx_TValue* rbx_index2adr(std::uintptr_t rl, int idx);

extern func_defs::rbx_getscheduler_t rbx_getscheduler;
extern func_defs::rbx_getstate_t rbx_getstate;
extern func_defs::rbx_output_t rbx_output;
extern func_defs::rbx_pushvfstring_t rbx_pushvfstring;
extern func_defs::rbx_index2psuedo_t rbx_index2psuedo;