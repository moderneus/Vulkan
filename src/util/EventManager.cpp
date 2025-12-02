#include "util/EventManager.hpp"

void Engine::Utils::EventManager::pollEvents(Engine::Window::Window& window)
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
