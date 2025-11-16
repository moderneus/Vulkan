#include "gfx/Renderer.hpp"
#include "util/EventManager.hpp"
#include "core/Core.hpp"

#include <SDL3/SDL.h>
#include <fmt/core.h>

void Renderer::init()
{
    sdlContext.init();
    window.create("Vulkan", 640, 480);
    vkCore.init();
}

void Renderer::destroy()
{
    window.destroy();
    sdlContext.destroy();
    vkCore.destroy();
}

void Renderer::draw()
{
    while(!window.closed())
        e.pollEvents(window);
}
