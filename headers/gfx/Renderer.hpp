#pragma once

#include "window/Window.hpp"
#include "util/EventManager.hpp"
#include "core/Core.hpp"
#include "core/SDL.hpp"

class Renderer
{
private:     
    Window window;
    SDL sdlContext;
    EventManager e;
    Core vkCore;
    
    void initSDL();
    void pollEvents();
    
public: 
    void init();
    void destroy();
    void draw();
};
