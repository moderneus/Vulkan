#include "core/SDL.hpp"
#include "util/String.hpp"
#include "util/Logger.hpp"

#include <SDL3/SDL.h>
#include <fmt/core.h>

void Engine::Core::SDL::init()
{
    Engine::Utils::Logger::get()->info("Initializing the SDL...");
    
    if(!SDL_Init(SDL_INIT_VIDEO))
        Engine::Utils::Logger::get()->critical("Cannot Initialize SDL::" + cstrToString(SDL_GetError()));

    isInit = true;

    Engine::Utils::Logger::get()->success("The SDL was initialiazed!");
}

void Engine::Core::SDL::destroy()
{
    Engine::Utils::Logger::get()->info("Quitting SDL...");
    
    if(!isInit)
        Engine::Utils::Logger::get()->critical("Cannot free the SDL memory::SDL initialiazed.");

    SDL_Quit();
    
    isInit = false;

    Engine::Utils::Logger::get()->success("SDL quit!");
}
