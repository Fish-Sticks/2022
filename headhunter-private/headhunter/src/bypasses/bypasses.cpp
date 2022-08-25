#include <cstdint>
#include "bypasses/bypasses.h"
#include "addresses/addresses.hpp"
#include "api/api.h"


namespace callcheck_
{
	std::uintptr_t backup = 0;
	std::uintptr_t old_val = 0;
	int custom_func_handler(std::uintptr_t rl) // acts as a proxy
	{
		std::uintptr_t func = rbx_index2adr(rl, -10003)->Value.p; // get upval
		return reinterpret_cast<int(__cdecl*)(std::uintptr_t)>(encryption::rbx_decrypt_closure(func))(rl);
	}

	void __declspec(naked) custom_func_proxy() // decides if the call is actually from lua, or just bc we overwrote some random fucking addy in oblivion
	{
		__asm
		{
			mov backup, eax
			pop eax

			cmp eax, addresses::callcheck_addy_3

			push eax
			mov eax, backup

			je call_handler

			push old_val
			ret
		call_handler:
			push custom_func_handler
			ret
		}
	}
}

void bypasses::callcheck()
{
	static bool init = false;
	if (!init)
	{
		init = true;
		callcheck_::old_val = *reinterpret_cast<std::uintptr_t*>(addresses::callcheck_addy_1);
		*reinterpret_cast<std::uintptr_t*>(addresses::callcheck_addy_1) = reinterpret_cast<std::uintptr_t>(callcheck_::custom_func_proxy);
	}
}