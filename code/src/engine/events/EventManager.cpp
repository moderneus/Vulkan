#include "engine/events/EventManager.hpp"
#include "engine/gfx/Renderer.hpp"
#include "engine/window/Window.hpp"

void event_manager_poll_events(event_manager_t* event_manager, renderer_state_t* st, window_t* window) 
{
	while(SDL_PollEvent(&event_manager->event)) {
		switch(event_manager->event.type) {
		case SDL_EVENT_QUIT:
			window->is_closed = true;
		break;

		case SDL_EVENT_WINDOW_RESIZED:
			st->framebuffer_resized = true;
		break;
		}
	}
}
