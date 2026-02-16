#ifndef MOD_EVENT_MANAGER_HPP
#define MOD_EVENT_MANAGER_HPP

#include "SDL3/SDL_events.h"

struct window_t;
struct renderer_state_t;

struct event_manager_t
{
	SDL_Event e;
};

void ev_m_poll(event_manager_t *ev_m, renderer_state_t *st, window_t *win);

#endif
