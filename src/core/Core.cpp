#include "core/Core.hpp"
#include "util/Logger.hpp"

void Engine::Core::Core::init()
{
    Engine::Utils::log->info("Initializing a Core...");
    
    vkInstance.create();

    Engine::Utils::log->success("The Core was Initialized!");
}

void Engine::Core::Core::destroy()
{
    Engine::Utils::log->info("Destroying the Core...");
    
    vkInstance.destroy();

    Engine::Utils::log->success("The Core was Destroyed!");
}

Engine::Core::Instance& Engine::Core::Core::getInstance()
{
    return vkInstance;
}
