#pragma once
#include <string>
#include <cstdint>
#include <vector>
#include <optional>

class instance_t
{
private:
	std::uintptr_t instance_ptr;
public:
	explicit instance_t(std::uintptr_t ptr) : instance_ptr{ ptr } {};
	explicit instance_t(void* ptr) : instance_ptr{ reinterpret_cast<std::uintptr_t>(ptr) } {};

	std::string get_name() const;
	std::string get_class() const;

	std::optional<instance_t> get_child_by_name(const std::string& name) const;
	std::optional<instance_t> get_child_by_class(const std::string& class_name) const;
	std::vector<instance_t> get_children() const;
	instance_t get_parent() const;
	instance_t get_datamodel() const;

	std::uintptr_t get_pointer() const;
	bool is_valid() const;
};