#pragma once

#include "window/Window.hpp"
#include "util/EventManager.hpp"
#include "util/Logger.hpp"
#include "core/Core.hpp"
#include "core/SDL.hpp"

namespace Engine
{
    namespace gfx
    {
        class Renderer
        {
        private:     
            Engine::Window::Window window;
            Engine::Core::SDL sdlContext;
            Engine::Utils::EventManager e;
            Engine::Core::Core vkCore;

        public: 
            void init();
            void destroy();
            void draw();
        };
    }
}
