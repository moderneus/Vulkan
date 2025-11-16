#include "core/SDL.hpp"
#include "util/String.hpp"
#include "util/Logger.hpp"

#include <SDL3/SDL.h>
#include <fmt/core.h>

void Engine::Core::SDL::init()
{
    Engine::Utils::log->info("Initializing the SDL...");
    
    if(!SDL_Init(SDL_INIT_VIDEO))
        Engine::Utils::log->critical("Cannot Initialize SDL::" + cstrToString(SDL_GetError()));

    isInit = true;

    Engine::Utils::log->success("The SDL was initialiazed!");
}

void Engine::Core::SDL::destroy()
{
    Engine::Utils::log->info("Quitting SDL...");
    
    if(!isInit)
        Engine::Utils::log->critical("Cannot free the SDL memory::SDL initialiazed.");

    SDL_Quit();
    
    isInit = false;

    Engine::Utils::log->success("SDL quit!");
}
