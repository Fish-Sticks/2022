#include "console/include/console.h"

void make_console(const std::string& title)
{
	DWORD old;
	FILE* f;

	VirtualProtect(&FreeConsole, 1, PAGE_EXECUTE_READWRITE, &old);
	*reinterpret_cast<byte*>(&FreeConsole) = 0xC3;
	VirtualProtect(&FreeConsole, 1, old, &old);

	AllocConsole();

	freopen_s(&f, "CONOUT$", "w", stdout);
	freopen_s(&f, "CONOUT$", "w", stderr);
	freopen_s(&f, "CONIN$", "r", stdin);

	SetConsoleTitleA(title.c_str());
}