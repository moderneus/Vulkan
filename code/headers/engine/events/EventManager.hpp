#ifndef MOD_EVENT_MANAGER_HPP
#define MOD_EVENT_MANAGER_HPP

#include "SDL3/SDL_events.h"

struct window_t;
struct renderer_config_t;

struct event_manager_t
{
	SDL_Event event;
};

void event_manager_poll_events(event_manager_t* event_manager, renderer_config_t* cfg, window_t* window);

#endif
