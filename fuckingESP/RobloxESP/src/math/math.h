#pragma once
#include <cstdint>

struct Vector2_t
{
	float x, y = 0;
};

struct Vector3_t : public Vector2_t
{
	float z = 0;
};

struct Vector4_t : public Vector3_t
{
	float w = 0;
};
