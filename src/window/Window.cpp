#include "window/Window.hpp"

Window::Window(const char* title, const unsigned int width, const unsigned int height)
{
    pWindow = SDL_CreateWindow(title, width, height, SDL_WINDOW_VULKAN);
}

Window::~Window()
{
    SDL_DestroyWindow(pWindow);
}

SDL_Window* Window::get()
{
    return pWindow;
}
