#include "engine/engine.hpp"
#include "core/vulkan/core.hpp"
#include "core/sdl/sdl_ctx.hpp"
#include "util/debug/log.hpp"

void engine_init(engine *e) 
{
	log_init();
	sdl_ctx_init();
	window_create(&e->win, "Vulkan", 640, 480);
	core_init(&e->vk_core, e->win);
	renderer_init(&e->rndr, &e->win);
}

void engine_destroy(engine *e) 
{
	renderer_destroy(&e->rndr);
	core_destroy(&e->vk_core);
	window_destroy(e->win);
	sdl_ctx_destroy();
	log_destroy();
}

void engine_run(engine *e) 
{
	renderer_loop(&e->rndr, &e->ev_m, &e->vk_core);
}
