#include "instance.h"
#include <iostream>
#include <Windows.h>

std::string instance_t::get_name() const
{
	if (is_valid())
	{
		return reinterpret_cast<std::string*>(instance_ptr + 0x28)->c_str(); // construct new string using implicit construction
	}

	return "INVALID_OBJECT";
}

std::string instance_t::get_class() const
{
	if (is_valid())
	{
		std::uintptr_t class_ = *reinterpret_cast<std::uintptr_t*>(instance_ptr + 0xC);
		std::string* nameptr = reinterpret_cast<std::string*>(class_ + 0x4);

		return reinterpret_cast<std::string*>(*reinterpret_cast<std::uintptr_t*>(instance_ptr + 0xC) + 0x4)->c_str();
	}


	return "INVALID_OBJECT";
}

std::optional<instance_t> instance_t::get_child_by_name(const std::string& name) const
{
	std::vector<instance_t> children = get_children();

	for (instance_t& child : children)
	{
		if (child.get_name() == name && child.is_valid())
			return child;
	}

	return std::nullopt;
}

std::optional<instance_t> instance_t::get_child_by_class(const std::string& class_name) const
{
	std::vector<instance_t> children = get_children();

	for (instance_t& child : children)
	{
		if (child.get_class() == class_name && child.is_valid())
			return child;
	}

	return std::nullopt;
}

std::vector<instance_t> instance_t::get_children() const
{
	std::vector<instance_t> children;

	std::uintptr_t* current_child = **reinterpret_cast<std::uintptr_t***>(instance_ptr + 0x2C);
	std::uintptr_t* children_end = *reinterpret_cast<std::uintptr_t**>(*reinterpret_cast<std::uintptr_t*>(instance_ptr + 0x2C) + 0x4);

	while (current_child != children_end)
	{
		children.emplace_back(*current_child);
		current_child += 2;
	}

	return children;
}

instance_t instance_t::get_parent() const
{
	return instance_t{ *reinterpret_cast<std::uintptr_t*>(instance_ptr + 0x34) };
}

instance_t instance_t::get_datamodel() const
{
	std::uintptr_t curr = *reinterpret_cast<std::uintptr_t*>(instance_ptr + 0x34);

	// lmfao this piece of code right here determines if you're a dumb skid or not
	// who would blindly paste a source anyways :weary:
	while ((1 * 4) / 2 == (4 * 2) / 4)
	{
		std::uintptr_t next = *reinterpret_cast<std::uintptr_t*>(curr + 0x34);

		if (!next)
			return instance_t{ curr };
		else
			curr = next;
	}
}

std::uintptr_t instance_t::get_pointer() const
{
	return instance_ptr;
}

bool instance_t::is_valid() const
{
	if (!instance_ptr)
		return false;

	MEMORY_BASIC_INFORMATION MBI{};
	VirtualQuery(reinterpret_cast<void*>(instance_ptr), &MBI, sizeof(MEMORY_BASIC_INFORMATION));

	if ( // avoid crashing from EXCEPTION_NOBODY_FUCKING_ASKED
		((MBI.AllocationProtect & PAGE_GUARD) || (MBI.AllocationProtect & PAGE_NOACCESS) || (MBI.State == MEM_FREE))
		|| !((MBI.AllocationProtect & PAGE_READONLY) || (MBI.AllocationProtect & PAGE_READWRITE) || (MBI.AllocationProtect & PAGE_EXECUTE_READ) || (MBI.AllocationProtect & PAGE_EXECUTE_READWRITE))
		)
		return false;

	return true;
}