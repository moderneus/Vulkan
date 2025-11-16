#include "window/Window.hpp"

#include <fmt/core.h>

void Window::create(const char* title, const unsigned int width, const unsigned int height)
{
    pWindow = SDL_CreateWindow(title, width, height, SDL_WINDOW_VULKAN);
}

void Window::destroy()
{
    SDL_DestroyWindow(pWindow);
}

void Window::close()
{
    isClosed = true;
}

bool Window::closed()
{
    return isClosed;
}

SDL_Window* Window::get()
{
    return pWindow;
}
