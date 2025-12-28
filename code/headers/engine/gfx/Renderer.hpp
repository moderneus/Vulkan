#pragma once

#include "util/EventManager.hpp"

struct Core;

struct Renderer {
    Window* pwindow;
    EventManager event_manager;
};

void renderer_init(Renderer* renderer, Window* pwindow);

void renderer_destroy(Renderer* renderer);

void renderer_loop(Renderer* renderer, const Core* vk_core);

void renderer_draw(const Core* vk_core);
