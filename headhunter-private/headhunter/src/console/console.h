#pragma once
#include <Windows.h>
#include <iostream>

class console_t
{
private:
	FILE* f_ptr = nullptr;
public:
	enum class color
	{
		red,
		green,
		blue,
		cyan,
		white,
		pink
	};

	explicit console_t(const std::string& title);
	~console_t();

	const console_t& operator<<(const std::string& str) const;
	const console_t& operator<<(color col) const;
	const console_t& operator<<(uintptr_t num) const;
};


extern const console_t output;