#ifndef MOD_EVENT_MANAGER_HPP
#define MOD_EVENT_MANAGER_HPP

#include "SDL3/SDL_events.h"

struct window;
struct renderer_state;

struct event_manager {
	SDL_Event event;
};

void event_manager_poll(event_manager *ev_m, renderer_state *st, window *win);

#endif
