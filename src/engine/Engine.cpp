#include "engine/Engine.hpp"
#include "core/Core.hpp"
#include "util/debug/Logger.hpp"

void Engine::Engine::init()
{
    Utils::Logger::get()->info("Initializing Engine...");
    
    sdlContext.init();
    window.create("Vulkan", 640, 480);
    Core::Core::get()->init();
    renderer.init(&window);

    Utils::Logger::get()->success("Engine was Initialized!");
}

void Engine::Engine::destroy()
{
    Utils::Logger::get()->info("Destroying Engine...");
    
    renderer.destroy();
    Core::Core::get()->destroy();
    window.destroy();
    sdlContext.destroy();

    Utils::Logger::get()->success("Engine was Destroyed!");
}

void Engine::Engine::run()
{
    renderer.draw();
}
