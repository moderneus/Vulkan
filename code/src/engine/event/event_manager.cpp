#include "engine/event/event_manager.hpp"
#include "engine/gfx/renderer.hpp"
#include "engine/window/window.hpp"

void event_manager_poll(event_manager *ev_m, renderer_state *st, window *win) 
{
	while(SDL_PollEvent(&ev_m->event)) {
		switch(ev_m->event.type) {
		case SDL_EVENT_QUIT:
			win->is_closed = true;
		break;

		case SDL_EVENT_WINDOW_RESIZED:
			st->fb_resized= true;
		break;
		}
	}
}
