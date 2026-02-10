#include "engine/Engine.hpp"
#include "core/vulkan/Core.hpp"
#include "core/SDL/SDL.hpp"
#include "util/debug/Logger.hpp"

void engine_init(engine_t* e) 
{
	log_init();
	SDL_ctx_init();
	win_create(&e->win, "Vulkan", 640, 480);
	core_init(&e->core, e->win);
	rndr_init(&e->rndr, &e->win);
}

void engine_destroy(engine_t* e) 
{
	rndr_destroy(&e->rndr);
	core_destroy(&e->core);
	win_destroy(e->win);
	SDL_ctx_destroy();
	log_destroy();
}

void engine_run(engine_t* e) 
{
	rndr_loop(&e->rndr, &e->ev_m, &e->core);
}
