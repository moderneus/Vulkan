#pragma once

#include "core/vulkan/Core.hpp"
#include "engine/window/Window.hpp"
#include "engine/gfx/Renderer.hpp"

struct Engine {
    Core vk_core;
    Window window;
    Renderer renderer;
};

void engine_init(Engine* engine);

void engine_destroy(Engine* engine);

void engine_run(Engine* engine);
