#ifndef MOD_ENGINE_HPP
#define MOD_ENGINE_HPP

#include "core/vulkan/core.hpp"
#include "engine/window/window.hpp"
#include "engine/gfx/renderer.hpp"
#include "engine/event/event_manager.hpp"

struct engine {
	core			vk_core;
	window			win;
	event_manager		ev_m;
	renderer		rndr;
};

void engine_init(engine *e);

void engine_destroy(engine *e);

void engine_run(engine *e);

#endif
