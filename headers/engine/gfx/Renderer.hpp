#pragma once

#include "engine/window/Window.hpp"
#include "util/EventManager.hpp"

struct Renderer {
    Window* pwindow;
    EventManager event_manager;
};

void renderer_init(Renderer* renderer, Window* pwindow);

void renderer_destroy(Renderer* renderer);

void renderer_loop(Renderer* renderer);

void renderer_draw();
