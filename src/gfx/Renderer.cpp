#include "gfx/Renderer.hpp"
#include "util/EventManager.hpp"
#include "util/debug/Logger.hpp"

void Engine::gfx::Renderer::init(Window::Window* pWindow)
{
    Utils::Logger::get()->info("Initializing a Renderer...");

    window = pWindow;
    
    Utils::Logger::get()->success("The Renderer was Initialized!");
}

void Engine::gfx::Renderer::destroy()
{
    Utils::Logger::get()->info("Destroying the Renderer...");

    window = nullptr;
    
    Utils::Logger::get()->success("The Renderer was Destroyed!");
}

void Engine::gfx::Renderer::loop()
{
    while(!window->closed())
        e.pollEvents(*window);
}

void Engine::gfx::Renderer::draw()
{
    loop();
}
