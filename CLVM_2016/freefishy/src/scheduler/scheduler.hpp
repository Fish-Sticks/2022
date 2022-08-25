#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <optional>

#include "../addresses.hpp"

class scheduler_t
{
private:
	std::uintptr_t task_scheduler = 0;
	scheduler_t(const scheduler_t&) = delete;
public:
	explicit scheduler_t()
	{
		this->task_scheduler = rbx_getscheduler();
	}

	std::vector<std::uintptr_t> get_jobs()
	{
		std::vector<std::uintptr_t> jobs{};

		std::uintptr_t job_start = *reinterpret_cast<std::uintptr_t*>(this->task_scheduler + offsets::scheduler::job_start);
		std::uintptr_t job_end = *reinterpret_cast<std::uintptr_t*>(this->task_scheduler + offsets::scheduler::job_end);

		for (std::uintptr_t current_job = job_start; current_job < job_end; current_job += 12)
		{
			jobs.push_back(*reinterpret_cast<std::uintptr_t*>(current_job));
		}

		return jobs;
	}

	std::optional<std::uintptr_t> get_job_by_name(const std::string& name)
	{
		for (std::uintptr_t job : this->get_jobs())
		{
			if (*reinterpret_cast<std::string*>(job + offsets::job::name) == name)
				return job;
		}

		return std::nullopt;
	}

	std::uintptr_t hook_job_vtable(std::uintptr_t job, void* dest)
	{
		std::uintptr_t* vtable = *reinterpret_cast<std::uintptr_t**>(job); // +0x1C = run
		std::uintptr_t* new_vtable = new std::uintptr_t[8]{}; // not freeing because its being used by roblox

		std::uintptr_t old = vtable[2];

		memcpy(new_vtable, vtable, 8 * 4);
		new_vtable[2] = reinterpret_cast<std::uintptr_t>(dest);

		*reinterpret_cast<std::uintptr_t**>(job) = new_vtable;
	
		return old;
	}
};