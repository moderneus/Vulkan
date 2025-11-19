#include "core/Core.hpp"
#include "util/debug/Logger.hpp"

Engine::Core::Instance Engine::Core::Core::vkInstance;

void Engine::Core::Core::init()
{
    Utils::Logger::get()->info("Initializing a Core...");
    
    vkInstance.create();

    Utils::Logger::get()->success("The Core was Initialized!");
}

void Engine::Core::Core::destroy()
{
    Utils::Logger::get()->info("Destroying the Core...");
    
    vkInstance.destroy();

    Utils::Logger::get()->success("The Core was Destroyed!");
}

VkInstance Engine::Core::Core::getInstance()
{
    return vkInstance.get();
}
