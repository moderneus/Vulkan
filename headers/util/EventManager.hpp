#pragma once

#include "window/Window.hpp"

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
