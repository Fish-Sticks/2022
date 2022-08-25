#pragma once
#include "addresses/addresses.hpp"
#include <cstdint>

// Basic intermediate structures, nothing that *will change*

struct FishValue // TValue rewrite, todo: add getter value which automatically reads tt and preforms decryption, would be really sweet
{
	std::uintptr_t value;
	std::uintptr_t extra[2];
    std::int32_t tt;
};

struct FishKey
{
    std::uintptr_t value;
    int extra[2];
    std::int32_t tt : 4;
    int next : 28; /* for chaining */
};

struct FishNode
{
    FishValue val;
    FishKey key;
};

using FishStk = FishValue*;