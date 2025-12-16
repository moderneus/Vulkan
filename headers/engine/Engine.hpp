#pragma once

#include "core/Core.hpp"
#include "window/Window.hpp"
#include "gfx/Renderer.hpp"

struct Engine {
    Core vk_core;
    Window window;
    Renderer renderer;
};

void engine_init(Engine* engine);

void engine_destroy(Engine* engine);

void engine_run(const Engine& engine);
