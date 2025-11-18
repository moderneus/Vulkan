#pragma once

#include "util/EventManager.hpp"

namespace Engine
{
    class Engine;

    namespace gfx
    {
        class Renderer
        {
            friend class ::Engine::Engine;
            
            Window::Window* window = nullptr;
            Utils::EventManager e;
            
            void init(Window::Window* window);
            void destroy();
            void loop();
            void draw();
            
            Renderer() = default;
        };
    }
}
