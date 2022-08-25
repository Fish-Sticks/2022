#include "addresses/addresses.hpp"
#include "addresses/declarations.hpp"
#include "api/include/util.h"
#include "api/include/structs.h"

void fish_increment_top(std::uintptr_t rL, std::int32_t amount)
{
	*reinterpret_cast<FishValue**>(rL + offsets::lua_state::top) += amount;
}

void fish_decrement_top(std::uintptr_t rL, std::int32_t amount)
{
	*reinterpret_cast<FishValue**>(rL + offsets::lua_state::top) -= amount;
}

std::int32_t fish_type(std::uintptr_t rL, std::int32_t idx)
{
	return fish_index2adr(rL, idx)->tt;
}