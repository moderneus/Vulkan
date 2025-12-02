#pragma once

#include "window/Window.hpp"

#include "SDL3/SDL_events.h"

namespace Engine
{
    namespace Utils
    {
        class EventManager
        {
        private:
            SDL_Event event;

        public:
            void pollEvents(Engine::Window::Window& window);
        };
    }
}
