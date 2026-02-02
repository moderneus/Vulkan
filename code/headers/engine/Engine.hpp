#ifndef MOD_ENGINE_HPP
#define MOD_ENGINE_HPP

#include "core/vulkan/Core.hpp"
#include "engine/window/Window.hpp"
#include "engine/gfx/Renderer.hpp"
#include "engine/events/EventManager.hpp"

struct engine_t
{
	core_t				vk_core;
	window_t			window;
	event_manager_t			event_manager;
	renderer_t			renderer;
};

void engine_init(engine_t* engine);

void engine_destroy(engine_t* engine);

void engine_run(engine_t* engine);

#endif
