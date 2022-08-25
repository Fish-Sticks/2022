#include "api/include/ltable.h"
#include "api/include/util.h"
#include "addresses/addresses.hpp"
#include "addresses/declarations.hpp"

#include <iostream>


const FishValue* fishH_getstr(std::uintptr_t t, std::uintptr_t key)
{
	FishNode* n = fish_hashstr(t, key);
	for (;;)
	{
		if (fish_ttisstring(fish_gkey(n)) && get_encrypted(fish_gkey(n)->value + offsets::string::hash, encryption::string::hash) == get_encrypted(key + offsets::string::hash, encryption::string::hash))
			return fish_gval(n);

		if (!fish_gnext(n))
			break;

		n += fish_gnext(n);
	}

	return reinterpret_cast<FishValue*>(addresses::fishO_nilobject);
}

const FishValue* fishH_get(std::uintptr_t t, const FishValue* key)
{
	switch (fish_ttype(key))
	{
		case fish_TNIL:
			return reinterpret_cast<FishValue*>(addresses::fishO_nilobject);
		case fish_TSTRING:
			return fishH_getstr(t, key->value);
		case fish_TNUMBER:
		{
			std::printf("Number key not implemented!\n");
			break;
		}
		default:
		{
			std::printf("Default key not implemented!\n");
		}
	}

	return reinterpret_cast<FishValue*>(addresses::fishO_nilobject);
}

FishValue* fishH_set(std::uintptr_t rL, std::uintptr_t t, const FishValue* key)
{
	const FishValue* p = fishH_get(t, key);
	*reinterpret_cast<char*>(t + offsets::table::flags) = 0;

	if (p != reinterpret_cast<FishValue*>(addresses::fishO_nilobject))
		return const_cast<FishValue*>(p);
	else
	{
		if (fish_ttisnil(key))
			fishG_runerror(rL, "table index is nil");

		std::printf("newkey is too hard to write so soorry but set didnt work~ uwu :(\n");
	}

	return reinterpret_cast<FishValue*>(addresses::fishO_nilobject);
}