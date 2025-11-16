#include "window/Window.hpp"
#include "util/StringUtils.hpp"
#include "util/Logger.hpp"

#include <fmt/core.h>

void Engine::Window::Window::create(const char* title, const unsigned int width, const unsigned int height)
{
    Engine::Utils::log->info("Creating a Window...");
    
    pWindow = SDL_CreateWindow(title, width, height, SDL_WINDOW_VULKAN);

    if(!pWindow)
        Engine::Utils::log->critical("Failed to create the Window::" + cstrToString(SDL_GetError()));

    Engine::Utils::log->success("The Window was Created!");
}

void Engine::Window::Window::destroy()
{
    Engine::Utils::log->info("Destroying the Window...");
    
    if(pWindow == nullptr)
        Engine::Utils::log->critical("Cannot Destroy the Window::Window is not Created!");
        
    SDL_DestroyWindow(pWindow);
    
    Engine::Utils::log->success("The Window was Destroyed!");
}

void Engine::Window::Window::close()
{
    isClosed = true;
}

bool Engine::Window::Window::closed()
{
    return isClosed;
}

SDL_Window* Engine::Window::Window::get()
{
    return pWindow;
}
