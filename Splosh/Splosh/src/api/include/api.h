#pragma once
#include <string>
#include <cstdint>


class RL
{
private:
	std::uintptr_t rL;
public:
	RL(std::uintptr_t rL);

	void push_nil();
	void push_boolean(bool b);
	void push_number(double n);
	void push_string(const char* str);

	void get_field(int idx, const char* field);
	void set_field(int idx, const char* field);

	void get_global(const char* field);
	void set_global(const char* field);

	int get_top();
	void set_top(int idx);
};