#include "core/objects/QueueFamily.hpp"
#include "util/debug/Logger.hpp"

#include <vulkan/vulkan.h>

#include <vector>
#include <cstdint>

uint32_t Engine::Core::QueueFamily::find(const VkPhysicalDevice& device)
{
    uint32_t queueFamilyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyProperties.data());

    bool found = false;
    for(size_t i = 0; i < queueFamilyProperties.size(); ++i)
    {
        if(queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            indecies = i;
            found = true;
            break;
        }
    }

    if(!found)
        Utils::Logger::get()->critical("Failed to Find Suitables Queues Families!");

    return indecies;
}