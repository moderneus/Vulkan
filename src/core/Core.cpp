#include "core/Core.hpp"
#include "util/debug/Logger.hpp"

void Engine::Core::Core::init()
{
    Utils::Logger::get()->info("Initializing a Core...");
    
    vkInstance.create();
    vkSurface.create();
    vkPhysicalDevice.pick(vkSurface);
    vkLogicalDevice.create(vkPhysicalDevice, vkSurface);
    vkSwapchain.create(vkPhysicalDevice, vkLogicalDevice, vkSurface);
    vkImageView.create(vkLogicalDevice);

    Utils::Logger::get()->success("The Core was Initialized!");
}

void Engine::Core::Core::destroy()
{
    Utils::Logger::get()->info("Destroying the Core...");

    vkImageView.destroy(vkLogicalDevice);
    vkSwapchain.destroy(vkLogicalDevice);
    vkLogicalDevice.destroy();
    vkSurface.destroy();
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