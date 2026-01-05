#pragma once

#include "SDL3/SDL_events.h"

struct Window;

struct EventManager {
    SDL_Event event;
};

void event_manager_poll_events(EventManager* event_manager, Window* window);
