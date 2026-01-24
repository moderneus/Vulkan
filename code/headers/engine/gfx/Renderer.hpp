#ifndef MOD_RENDERER_HPP
#define MOD_RENDERER_HPP

#include "util/EventManager.hpp"

struct window_t;
struct core_t;

struct renderer_t
{
	window_t*		pwindow;
	event_manager_t		event_manager;
};

void renderer_init(renderer_t* renderer, window_t* pwindow);

void renderer_destroy(renderer_t* renderer);

void renderer_loop(renderer_t* renderer, const core_t* vk_core);

void renderer_draw(const core_t* vk_core);

#endif
