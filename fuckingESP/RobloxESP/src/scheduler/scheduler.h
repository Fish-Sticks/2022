#pragma once
#include <string>
#include <cstdint>
#include <instance/instance.h>

class scheduler_t
{
private:
	std::uintptr_t task_scheduler = 0;

	scheduler_t() {};
	scheduler_t operator=(scheduler_t) {};
public:
	static scheduler_t& get();
	std::uintptr_t get_scheduler(); // call this before anything else.
	instance_t get_datamodel();
	std::uintptr_t get_job_by_name(const std::string& name);
};