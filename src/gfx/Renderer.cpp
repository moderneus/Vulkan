#include "gfx/Renderer.hpp"
#include "util/EventManager.hpp"
#include "util/Logger.hpp"
#include "core/Core.hpp"

void Engine::gfx::Renderer::init()
{
    Engine::Utils::log->info("Initializing a Renderer...");
    
    sdlContext.init();
    window.create("Vulkan", 640, 480);
    vkCore.init();

    Engine::Utils::log->success("The Renderer was Initialized!");
}

void Engine::gfx::Renderer::destroy()
{
    Engine::Utils::log->info("Destroying the Renderer...");
    
    window.destroy();
    sdlContext.destroy();
    vkCore.destroy();

    Engine::Utils::log->success("The Renderer was Destroyed!");
}

void Engine::gfx::Renderer::draw()
{
    while(!window.closed())
        e.pollEvents(window);
}
