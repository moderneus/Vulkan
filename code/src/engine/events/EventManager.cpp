#include "engine/events/EventManager.hpp"
#include "engine/gfx/Renderer.hpp"
#include "engine/window/Window.hpp"

void ev_m_poll(event_manager_t *ev_m, renderer_state_t *st, window_t *win) 
{
	while(SDL_PollEvent(&ev_m->e)) {
		switch(ev_m->e.type) {
		case SDL_EVENT_QUIT:
			win->is_closed = true;
		break;

		case SDL_EVENT_WINDOW_RESIZED:
			st->fb_resized= true;
		break;
		}
	}
}
