#pragma once

#include "window/Window.hpp"
#include "util/EventManager.hpp"

struct Renderer {
    Window* pwindow;
    EventManager event_manager;
};

void renderer_init(Renderer* renderer);

void renderer_destroy(Renderer* renderer);

void renderer_loop(const Renderer& renderer);

void renderer_draw(const Renderer& renderer);
