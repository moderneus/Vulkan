#include "core/objects/PhysicalDevice.hpp"
#include "core/Core.hpp"
#include "util/debug/Logger.hpp"

#include <vector>
#include <map>

int Engine::Core::PhysicalDevice::ratePhysicalDevice(const VkPhysicalDevice& device)
{
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    
    int score = 0;
    if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        score += 1000;

    score += deviceProperties.limits.maxImageDimension2D;
    
    return score;
}

void Engine::Core::PhysicalDevice::pick()
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(Core::Core::get()->getInstance(), &deviceCount, nullptr);

    if(deviceCount == 0)
        Utils::Logger::get()->critical("Failed to find GPU with Vulkan support!");

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(Core::Core::get()->getInstance(), &deviceCount, devices.data());

    std::multimap<int, VkPhysicalDevice> candidates;

    for(const VkPhysicalDevice& device : devices)
    {
        int score = ratePhysicalDevice(device);
        candidates.insert(std::make_pair(score, device));
    }

    if(candidates.rbegin()->first > 0)
        physicalDevice = candidates.rbegin()->second;

    else
        Utils::Logger::get()->critical("Failed to Find any Suitable GPU!");
}

VkPhysicalDevice Engine::Core::PhysicalDevice::get()
{
    return physicalDevice;
}
