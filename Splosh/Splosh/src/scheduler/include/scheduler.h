#pragma once
#include <Windows.h>
#include <string>
#include <vector>

class scheduler_t
{
private:
	mutable std::uintptr_t taskscheduler = 0;
	mutable std::uintptr_t datamodel = 0;
	mutable std::uintptr_t script_context = 0;
public:
	explicit scheduler_t();
	std::uintptr_t get() const;
	std::uintptr_t get_datamodel() const;
	std::uintptr_t get_script_context() const;
	std::uintptr_t get_global_luastate() const;
	std::vector<std::uintptr_t> get_jobs() const;
	std::uintptr_t get_waiting_scripts_job() const;
	void print_jobs() const;
	void hook_waiting_scripts_job(void* hook, std::uintptr_t& original_func) const;
	void set_fps(double fps) const;
	void begin() const;
};

extern const scheduler_t scheduler;