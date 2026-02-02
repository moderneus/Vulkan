#ifndef MOD_RENDERER_HPP
#define MOD_RENDERER_HPP

#include <cstdint>

struct event_manager_t;
struct window_t;
struct core_t;

struct renderer_t
{
	window_t* pwindow;
};

struct renderer_config_t
{
	uint32_t current_frame = 0;
	bool framebuffer_resized = false;
};

void renderer_init(renderer_t* renderer, window_t* pwindow);

void renderer_destroy(renderer_t* renderer);

void renderer_loop(renderer_t* renderer, event_manager_t* event_manager, core_t* vk_core);

void renderer_draw(const renderer_t& renderer, renderer_config_t* cfg, core_t* vk_core);

#endif
