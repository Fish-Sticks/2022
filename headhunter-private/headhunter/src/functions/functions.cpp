#include "functions/functions.h"
#include "addresses/addresses.hpp"
#include "console/console.h"
#include "api/api.h"
#include "execution/execution.h"

#include <intrin.h>

#define CURL_STATICLIB

#include <curl/curl.h>
#include <curl/easy.h>


size_t write_callback(char* ptr, size_t size, size_t nmemb, void* userdata)
{
	std::string* str = reinterpret_cast<std::string*>(userdata);
	str->append(ptr, size * nmemb);
	return size * nmemb;
}



namespace custom_funcs
{
	int setreadonly(std::uintptr_t rl)
	{
		rbx_TValue* tbl = rbx_index2adr(rl, 1);
		*reinterpret_cast<bool*>(tbl->Value.p + offsets::table::readonly) = rbx_toboolean(rl, 2);
		return 0;
	}

	int getrawmetatable(std::uintptr_t rl)
	{
		rbx_TValue& base = **reinterpret_cast<rbx_TValue**>(rl + offsets::luastate::base);
		rbx_TValue& top = **reinterpret_cast<rbx_TValue**>(rl + offsets::luastate::top);

		std::uintptr_t enc_mt = base.Value.p + (base.tt == ttypes["table"] ? offsets::table::metatable : offsets::userdata::metatable);

		if (std::uintptr_t mt = encryption::rbx_decrypt_metatable(enc_mt))
		{
			top.Value.p = mt;
			top.tt = ttypes["table"];
			rbx_increment_top(rl, 1);
			return 1;
		}
		return 0;
	}

	int setfpscap(std::uintptr_t rl)
	{
		execution.set_fps(rbx_tonumber(rl, 1));
		return 0;
	}

	int setidentity(std::uintptr_t rl) // use yield to reset LSI
	{
		rbx_setidentity(rl, rbx_tonumber(rl, 1));
		return 0;
	}

	int loadstring(std::uintptr_t rl)
	{
		const char* script = rbx_tostring(rl, 1);

		roblox_encoder_t roblox_encoder{};
		const std::string compiled = Luau::compile(script, {}, {}, &roblox_encoder);
		rbx_deserialize(rl, "headhunter.exe", compiled.c_str(), compiled.size());
		return 1;
	}

	int getfuncaddy(std::uintptr_t rl) // if you know how to use this, everything else in this exploit will be hella easy to make
	{
		std::uintptr_t func = encryption::rbx_decrypt_closure(**reinterpret_cast<std::uintptr_t**>(rl + offsets::luastate::base));
		printf_s("0x%08X\n", func - reinterpret_cast<std::uintptr_t>(GetModuleHandle(NULL)));
		return 0;
	}

	int getnamecallmethod(std::uintptr_t rl)
	{
		if (std::uintptr_t method = *reinterpret_cast<std::uintptr_t*>(rl + offsets::luastate::namecallmethod))
		{
			rbx_pushstring(rl, reinterpret_cast<const char*>(method + offsets::string::data));
			return 1;
		}
		return 0;
	}

	int httpget(std::uintptr_t rl)
	{
		const char* url = rbx_tostring(rl, 1);

		CURL* curl = curl_easy_init();

		if (curl)
		{
			std::string result;
			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);

			curl_easy_perform(curl);
			curl_easy_cleanup(curl);

			rbx_pushstring(rl, result);
			return 1;
		}

		return 0;
	}

	int speedhack(std::uintptr_t rl)
	{
		rbx_getglobal(rl, "game");
		rbx_getfield(rl, -1, "Players");
		rbx_getfield(rl, -1, "LocalPlayer");
		rbx_getfield(rl, -1, "Character");
		rbx_getfield(rl, -1, "Humanoid");
		rbx_pushnumber(rl, 150);
		rbx_setfield(rl, -2, "WalkSpeed");
		return 1;
	}
}