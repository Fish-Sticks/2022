#include "visual_engine.h"
#include <scheduler/scheduler.h>

visual_engine_t* get_visual_engine()
{
	std::printf("Task scheduler: 0x%08X\n", scheduler_t::get().get_scheduler());

	std::uintptr_t job = scheduler_t::get().get_job_by_name("Render");
	std::uintptr_t render_view = *reinterpret_cast<std::uintptr_t*>(job + 0x148);

	return *reinterpret_cast<visual_engine_t**>(render_view + 0x8);
}