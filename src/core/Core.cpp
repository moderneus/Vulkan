#include "core/Core.hpp"
#include "util/debug/Logger.hpp"

void Engine::Core::Core::init()
{
    Engine::Utils::Logger::get()->info("Initializing a Core...");
    
    vkInstance.create();

    Engine::Utils::Logger::get()->success("The Core was Initialized!");
}

void Engine::Core::Core::destroy()
{
    Engine::Utils::Logger::get()->info("Destroying the Core...");
    
    vkInstance.destroy();

    Engine::Utils::Logger::get()->success("The Core was Destroyed!");
}

Engine::Core::Instance& Engine::Core::Core::getInstance()
{
    return vkInstance;
}
