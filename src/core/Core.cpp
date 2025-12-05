#include "core/Core.hpp"
#include "util/debug/Logger.hpp"

void Engine::Core::Core::init(const Window::Window& window)
{
    Utils::Logger::get()->info("Initializing a Core...");
    
    vkInstance.create();
    vkPhysicalDevice.pick();
    vkLogicalDevice.create(vkPhysicalDevice);
    vkSurface.create(window);

    Utils::Logger::get()->success("The Core was Initialized!");
}

void Engine::Core::Core::destroy()
{
    Utils::Logger::get()->info("Destroying the Core...");
    
    vkSurface.destroy();
    vkLogicalDevice.destroy();
    vkInstance.destroy();

    Utils::Logger::get()->success("The Core was Destroyed!");
}

VkInstance Engine::Core::Core::getInstance()
{
    return vkInstance.get();
}

VkPhysicalDevice Engine::Core::Core::getPhysicalDevice()
{
    return vkPhysicalDevice.get();
}