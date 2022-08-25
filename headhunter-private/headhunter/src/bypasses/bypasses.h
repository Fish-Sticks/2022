#pragma once
#include "addresses/addresses.hpp"

namespace bypasses // todo: retcheck, callcheck, memcheck, trustcheck maybe?
{
	extern void callcheck();


	namespace retcheck_
	{
		static void __declspec(noinline) __declspec(naked) stub()
		{
			__asm
			{
				pop edi
				push addresses::fake_ret_addy
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
}