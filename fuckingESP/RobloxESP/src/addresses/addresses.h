#pragma once
#include <Windows.h>
#include <cstdint>

const std::uintptr_t current_module = reinterpret_cast<std::uintptr_t>(GetModuleHandle(NULL));

using rbx_getscheduler_t = std::uintptr_t(__cdecl*)();
extern rbx_getscheduler_t rbx_getscheduler;


const std::uintptr_t rbx_getscheduler_addy = current_module + 0xDE90B0;