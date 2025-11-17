#include "window/Window.hpp"
#include "util/String.hpp"
#include "util/Logger.hpp"

#include <fmt/core.h>

void Engine::Window::Window::create(const char* title, const unsigned int width, const unsigned int height)
{
    Engine::Utils::Logger::get()->info("Creating a Window...");
    
    pWindow = SDL_CreateWindow(title, width, height, SDL_WINDOW_VULKAN);

    if(!pWindow)
        Engine::Utils::Logger::get()->critical("Failed to create the Window::" + cstrToString(SDL_GetError()));

    Engine::Utils::Logger::get()->success("The Window was Created!");
}

void Engine::Window::Window::destroy()
{
    Engine::Utils::Logger::get()->info("Destroying the Window...");
    
    if(pWindow == nullptr)
        Engine::Utils::Logger::get()->critical("Cannot Destroy the Window::Window is not Created!");
        
    SDL_DestroyWindow(pWindow);
    
    Engine::Utils::Logger::get()->success("The Window was Destroyed!");
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
