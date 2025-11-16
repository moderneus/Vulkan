#pragma once

#include <SDL3/SDL.h>

class Window
{
private:
    SDL_Window* pWindow;
    bool isClosed = false;
    
public:
    void create(const char* title, const unsigned int width, const unsigned int height);
    void destroy();
    void close();
    bool closed();
        
    SDL_Window* get();
};
