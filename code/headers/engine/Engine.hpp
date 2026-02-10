#ifndef MOD_ENGINE_HPP
#define MOD_ENGINE_HPP

#include "core/vulkan/Core.hpp"
#include "engine/window/Window.hpp"
#include "engine/gfx/Renderer.hpp"
#include "engine/events/EventManager.hpp"

struct engine_t
{
	core_t				core;
	window_t			win;
	event_manager_t			ev_m;
	renderer_t			rndr;
};

void engine_init(engine_t* e);

void engine_destroy(engine_t* e);

void engine_run(engine_t* e);

#endif
