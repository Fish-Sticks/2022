#include "scheduler.h"
#include <addresses/addresses.h>


scheduler_t& scheduler_t::get()
{
	static scheduler_t scheduler{};
	return scheduler;
}

std::uintptr_t scheduler_t::get_scheduler()
{
	this->task_scheduler = rbx_getscheduler();
	return this->task_scheduler;
}

instance_t scheduler_t::get_datamodel()
{
	std::uintptr_t job = get_job_by_name("Render"); // there's only one render job so the datamodel should be the real one. (You wouldn't render the fake one anyways.)
	std::uintptr_t datamodel = *reinterpret_cast<std::uintptr_t*>(job + 0x28) + 4;

	return instance_t{ datamodel };
}

std::uintptr_t scheduler_t::get_job_by_name(const std::string& name)
{
	std::uintptr_t* current_job = *reinterpret_cast<std::uintptr_t**>(this->task_scheduler + 0x134);

	while (*current_job != *reinterpret_cast<std::uintptr_t*>(this->task_scheduler + 0x138))
	{
		if (*reinterpret_cast<std::string*>(*current_job + 0x10) == name)
			return *current_job;

		current_job += 2;
	}
}