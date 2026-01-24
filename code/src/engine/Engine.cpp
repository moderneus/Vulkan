#include "engine/Engine.hpp"
#include "core/vulkan/Core.hpp"
#include "core/SDL/SDL.hpp"
#include "util/debug/Logger.hpp"

void engine_init(engine_t* engine) 
{
	log_info("Initializing Engine...");

	SDL_context_init();
	window_create(&engine->window, "Vulkan", 640, 480);
	vk_core_init(&engine->vk_core, engine->window);
	renderer_init(&engine->renderer, &engine->window);

	log_success("Engine was Initialized!");
}

void engine_destroy(engine_t* engine) 
{
	log_info("Destroying Engine...");

	renderer_destroy(&engine->renderer);
	vk_core_destroy(&engine->vk_core);
	window_destroy(engine->window);
	SDL_context_destroy();

	log_success("Engine was Destroyed!");
}

void engine_run(engine_t* engine) 
{
	renderer_loop(&engine->renderer, &engine->vk_core);
}
