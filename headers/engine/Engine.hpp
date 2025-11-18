#pragma once

#include "core/Core.hpp"
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
        Core::Core vkCore;
        gfx::Renderer renderer;
        
    public:
        void init();
        void destroy();
        void run();
    };
}
