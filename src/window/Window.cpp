#include "window/Window.hpp"
#include "util/String.hpp"
#include "util/debug/Logger.hpp"

#include <fmt/core.h>

void Engine::Window::Window::create(const char* title, const unsigned int width, const unsigned int height)
{
    Utils::Logger::get()->info("Creating a Window...");
    
    pWindow = SDL_CreateWindow(title, width, height, SDL_WINDOW_VULKAN);

    if(!pWindow)
        Utils::Logger::get()->critical("Failed to create the Window::" + Utils::cstrToString(SDL_GetError()));

    Utils::Logger::get()->success("The Window was Created!");
}

void Engine::Window::Window::destroy()
{
    Utils::Logger::get()->info("Destroying the Window...");
    
    if(pWindow == nullptr)
        Utils::Logger::get()->critical("Cannot Destroy the Window::Window is not Created!");
        
    SDL_DestroyWindow(pWindow);
    
    Utils::Logger::get()->success("The Window was Destroyed!");
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
