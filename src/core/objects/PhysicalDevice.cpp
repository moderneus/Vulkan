#include "core/objects/PhysicalDevice.hpp"
#include "core/Core.hpp"
#include "util/debug/Logger.hpp"

#include <vulkan/vulkan.h>

#include <vector>

void Engine::Core::PhysicalDevice::pick()
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(Engine::Core::Core::getInstance(), &deviceCount, nullptr);

    if(deviceCount == 0)
        Utils::Logger::get()->critical("Failed to find GPU with Vulkan support!");

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(Engine::Core::Core::getInstance(), &deviceCount, devices.data());

    for(const VkPhysicalDevice& device : devices)
        physicalDevice = device;
}

VkPhysicalDevice Engine::Core::PhysicalDevice::get()
{
    return physicalDevice;
}
