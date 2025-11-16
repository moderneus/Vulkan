#include "core/SDL.hpp"

#include <SDL3/SDL.h>
#include <fmt/core.h>

void SDL::init()
{
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        fmt::print("SDL Initialization failed!\n");
        std::exit(-1);
    }

    isInit = true;
}

void SDL::destroy()
{
    if(isInit)
        SDL_Quit();

    else
        fmt::print("Cannot free SDL memory: SDL is not initialiazed!\n");
    
    isInit = false;
}
