#pragma once
#include <Windows.h>
#include <cstdint>

template <typename T>
T trampoline_hook(void* addy, void* dest, std::size_t len)
{
	DWORD prot = NULL;
	void* mid = VirtualAlloc(nullptr, len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	VirtualProtect(addy, len + 5, PAGE_EXECUTE_READWRITE, &prot);

	memcpy(mid, addy, len);

	*reinterpret_cast<byte*>(addy) = 0xE9;
	*reinterpret_cast<std::uintptr_t*>(reinterpret_cast<std::uintptr_t>(addy) + 1) = reinterpret_cast<std::uintptr_t>(dest) - reinterpret_cast<std::uintptr_t>(addy) - 5;
	*reinterpret_cast<byte*>(reinterpret_cast<std::uintptr_t>(mid) + len) = 0xE9;
	*reinterpret_cast<std::uintptr_t*>(reinterpret_cast<std::uintptr_t>(mid) + len + 1) = reinterpret_cast<std::uintptr_t>(addy) - reinterpret_cast<std::uintptr_t>(mid) - 5;

	VirtualProtect(addy, len + 5, prot, &prot);
	VirtualProtect(mid, len + 5, PAGE_EXECUTE_READ, &prot);

	return reinterpret_cast<T>(mid);
}