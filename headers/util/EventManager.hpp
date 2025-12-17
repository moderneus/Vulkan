#pragma once

#include "engine/window/Window.hpp"

#include "SDL3/SDL_events.h"

struct EventManager {
    SDL_Event event;
};

void event_manager_poll_events(EventManager* event_manager, Window* window);
