#pragma once

#include <cstdint>
#include <math/math.h>
#include <instance/instance.h>


// Created with ReClass.NET 1.2 by KN4CK3R

/*
class visual_engine_t
{
public:
	std::uintptr_t* vtable; //0x0000
	char pad_0004[12]; //0x0004
	uint32_t frames_passed; //0x0010
	char pad_0014[76]; //0x0014
	Vector3_t camera_pos; //0x0060
	float view_matrix[16]; //0x006C
	float world_rotation_matrix[16]; //0x00AC
	float object_rotation_matrix[16]; //0x00EC
};
*/

/*
class visual_engine_t
{
public:
	char pad_0000[16]; //0x0000
	uint32_t frames_passed; //0x0010
	char pad_0014[1440]; //0x0014
	float N000001BF[16]; //0x05B4
	float N000001C0[16]; //0x05F4
	char pad_0634[268]; //0x0634
	float view_matrix[16]; //0x0740
	char pad_0780[12]; //0x0780
	std::uint32_t screen_x; //0x078C
	std::uint32_t screen_y; //0x0790
	char pad_0794[852]; //0x0794
}; //Size: 0x0AE8
*/

// Created with ReClass.NET 1.2 by KN4CK3R

class visual_engine_t
{
public:
	std::uintptr_t* vtable;
	char pad_0004[12]; //0x0004
	uint32_t frames_passed; //0x0010
	char pad_0014[1804]; //0x0014
	float view_matrix[16]; //0x0720
	char pad_0760[44]; //0x0760
	float screen_x; //0x078C
	float screen_y; //0x0790
}; //Size: 0x0794

visual_engine_t* get_visual_engine();