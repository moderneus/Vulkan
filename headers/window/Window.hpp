#pragma once

#include "SDL3/SDL_video.h"

struct Window {
    SDL_Window* pwindow;
    uint32_t width;
    uint32_t height;
    bool is_closed;
};

void window_create(Window* window, const char* title, const uint32_t width, const uint32_t height);

void window_destroy();
