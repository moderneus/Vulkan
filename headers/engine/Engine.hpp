#pragma once

#include "core/SDL.hpp"
#include "window/Window.hpp"
#include "gfx/Renderer.hpp"

namespace Engine
{
    class Engine
    {
    private: 
        Core::SDL sdlContext;
        Window::Window window;
        gfx::Renderer renderer;
        
    public:
        void init();
        void destroy();
        void run();
    };
}
