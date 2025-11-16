#pragma once

#include <SDL3/SDL.h>

class Window
{
private:
    SDL_Window* pWindow;
    
public:
    Window(const char* title, const unsigned int width, const unsigned int height);
    ~Window();
        
    SDL_Window* get();
};
