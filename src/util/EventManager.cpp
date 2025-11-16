#include "util/EventManager.hpp"

void EventManager::pollEvents(Window& window)
{
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_EVENT_QUIT:
                window.close();
            break;
        }
    }
}
