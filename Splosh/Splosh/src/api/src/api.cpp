#include "api/include/api.h"
#include "api/include/structs.h"
#include "api/include/util.h"
#include "api/include/lvm.h"
#include "api/include/lstring.h"

#include "addresses/declarations.hpp"


RL::RL(std::uintptr_t rL) : rL{ rL } {};

void RL::push_nil()
{

}

void RL::push_boolean(bool b)
{

}

void RL::push_number(double n)
{

}
	
void RL::push_string(const char* str)
{
	FishValue new_value{};
	new_value.value = fishS_new(rL, str);
	new_value.tt = fish_TSTRING;
	
	fish_setobj(*reinterpret_cast<FishValue**>(rL + offsets::lua_state::top), &new_value);
	fish_increment_top(rL, 1);
}

	
void RL::get_field(int idx, const char* field)
{

}
	
void RL::set_field(int idx, const char* field)
{
	FishStk t;
	FishValue key;

	t = fish_index2adr(rL, idx);

	key.value = fishS_new(rL, field);
	key.tt = fish_TSTRING;

	std::printf("Made key: 0x%p\n", key.value);

	fishV_settable(rL, t, &key, *reinterpret_cast<FishValue**>(rL + offsets::lua_state::top) - 1);
	fish_decrement_top(rL, 1);
}

void RL::get_global(const char* field)
{
	get_field(-10002, field);
}

void RL::set_global(const char* field)
{
	set_field(-10002, field);
}

int RL::get_top()
{
	return *reinterpret_cast<FishValue**>(rL + offsets::lua_state::top) - *reinterpret_cast<FishValue**>(rL + offsets::lua_state::base);
}

void RL::set_top(int idx)
{

}