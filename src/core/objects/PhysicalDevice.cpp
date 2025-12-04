#include "core/objects/PhysicalDevice.hpp"
#include "core/objects/QueueFamily.hpp"
#include "core/Core.hpp"
#include "util/debug/Logger.hpp"

#include <vulkan/vulkan.h>

#include <string>
#include <vector>
#include <map>

int Engine::Core::PhysicalDevice::rate(const VkPhysicalDevice& device)
{
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    
    int score = 0;
    if(deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        score += 1000;

    score += deviceProperties.limits.maxImageDimension2D;
    
    return score;
}

std::string Engine::Core::PhysicalDevice::name(const VkPhysicalDevice& device)
{
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    return deviceProperties.deviceName;
}

bool Engine::Core::PhysicalDevice::isSuitable(const VkPhysicalDevice& device)
{
    QueueFamily queueFamily;
    queueFamily.find(device);

    return true;
}

void Engine::Core::PhysicalDevice::pick()
{
    Utils::Logger::get()->info("Searching a Suitable GPU...");

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(Core::Core::get()->getInstance(), &deviceCount, nullptr);

    if(deviceCount == 0)
        Utils::Logger::get()->critical("Failed to find GPU with Vulkan support!");

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(Core::Core::get()->getInstance(), &deviceCount, devices.data());

    std::multimap<int, VkPhysicalDevice> candidates;

    for(const VkPhysicalDevice& device : devices)
    {
        int score = rate(device);
        candidates.insert(std::make_pair(score, device));
    }

    if(candidates.rbegin()->first > 0)
        physicalDevice = candidates.rbegin()->second;

    else if(!isSuitable(physicalDevice))
        Utils::Logger::get()->critical("Failed to Find any Suitable GPU!");

    else
        Utils::Logger::get()->critical("Failed to Find any Suitable GPU!");

    Utils::Logger::get()->success("The GPU was Found!");
    Utils::Logger::get()->info("Selected GPU = ", name(physicalDevice));
}

VkPhysicalDevice Engine::Core::PhysicalDevice::get()
{
    return physicalDevice;
}