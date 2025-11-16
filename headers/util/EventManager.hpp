#pragma once

#include "window/Window.hpp"

class EventManager
{
private:
    SDL_Event event;

public:
    void pollEvents(Window& window);
};
