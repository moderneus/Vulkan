#include "util/EventManager.hpp"

void event_manager_poll_events(EventManager* event_manager, Window* window) {
    while(SDL_PollEvent(&event_manager->event)) {
        switch(event_manager->event.type) {
            case SDL_EVENT_QUIT:
                window->is_closed = true;
            break;
        }
    }
}
