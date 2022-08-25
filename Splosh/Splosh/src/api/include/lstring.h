#pragma once
#include <cstdint>
#include <cstddef>
#include <cstring>
#include "addresses/addresses.hpp"

extern std::uintptr_t fishS_newlstr(std::uintptr_t rL, const char* str, std::size_t len);
extern void fish_dumpallstrings(std::uintptr_t rL);


/* string size limit */
#define MAXSSIZE (1 << 30)
#define sizestring(len) (offsets::string::data + len + 1)

#define fishS_new(rL, s) (fishS_newlstr(rL, s, strlen(s)))