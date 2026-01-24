#include "util/EventManager.hpp"
#include "engine/window/Window.hpp"

void event_manager_poll_events(event_manager_t* event_manager, window_t* window) 
{
	while(SDL_PollEvent(&event_manager->event)) {
		switch(event_manager->event.type) {
			case SDL_EVENT_QUIT:
				window->is_closed = true;
			break;
		}
	}
}
