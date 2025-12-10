#include "core/objects/QueueFamily.hpp"
#include "util/debug/Logger.hpp"

#include <vulkan/vulkan.h>

#include <vector>
#include <cstdint>

Engine::Core::Indices Engine::Core::QueueFamily::find(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface)
{
    Utils::Logger::get()->info("Seacrhing a Suitable Queue Families...");

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

    Indices indices;
    for (uint32_t i = 0; i < queueFamilyCount; ++i) 
    {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            indices.graphicsFamily = i;

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);

        if (presentSupport)
            indices.presentFamily = i;

        if (indices.isComplete())
            break;
    }

    if(!indices.isComplete())
        Utils::Logger::get()->critical("Failed to Find any Suitable Queue Families!");

    Utils::Logger::get()->success("The Suitable Queue Families was Found!");

    return indices;
}
