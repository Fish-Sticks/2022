#include "api/include/lvm.h"
#include "api/include/util.h"
#include "api/include/ltable.h"
#include "addresses/declarations.hpp"

void fishV_gettable(std::uintptr_t rL, const FishValue* t, FishValue* key, FishStk val)
{
	std::int32_t loop;
	for (loop = 0; loop < MAXTAGLOOP; ++loop)
	{
		const FishValue* tm;

		if (fish_ttistable(t))
		{
			std::uintptr_t h = t->value;

			const FishValue* res = fishH_get(h, key);

			if (!fish_ttisnil(res) || true)
			{
				fish_setobj(val, res);
				return;
			}
		}
	}
}


#include <iostream>
void fishV_settable(std::uintptr_t rL, const FishValue* t, FishValue* key, FishStk val)
{
	std::int32_t loop;
	FishValue temp;
	for (loop = 0; loop < MAXTAGLOOP; ++loop)
	{
		const FishValue* tm;
	
		if (fish_ttistable(t))
		{
			std::printf("it's a table!\n");

			std::uintptr_t h = t->value;

			if (*reinterpret_cast<bool*>(h + offsets::table::readonly))
				fishG_runerror(rL, "Attempt to modify readonly table");

			FishValue* oldval = fishH_set(rL, h, key);

			std::printf("finished! oldval: 0x%p\n", oldval);

			if (!fish_ttisnil(oldval) || true)
			{
				std::printf("not running setter!\n");
				// fish_setobj(oldval, val);
				// if (key->tt >= fish_TSTRING && (*reinterpret_cast<char*>(h + 2) & 4) != 0 && (*reinterpret_cast<char*>(val->value + 2) & 3) != 0) {}
					//fishC_barriertable(rL, h, val->value);

				return;
			}
		}
	}

	fishG_runerror(rL, "loop in settable");
}