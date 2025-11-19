#include "core/SDL.hpp"
#include "util/String.hpp"
#include "util/debug/Logger.hpp"

#include <SDL3/SDL.h>
#include <fmt/core.h>

void Engine::Core::SDL::init()
{
    Utils::Logger::get()->info("Initializing the SDL...");
    
    if(!SDL_Init(SDL_INIT_VIDEO))
        Utils::Logger::get()->critical("Cannot Initialize SDL::" + Utils::cstrToString(SDL_GetError()));

    isInit = true;

    Utils::Logger::get()->success("The SDL was initialiazed!");
}

void Engine::Core::SDL::destroy()
{
    Utils::Logger::get()->info("Quitting SDL...");
    
    if(!isInit)
        Utils::Logger::get()->critical("Cannot free the SDL memory::SDL initialiazed.");

    SDL_Quit();
    
    isInit = false;

    Utils::Logger::get()->success("SDL quit!");
}
