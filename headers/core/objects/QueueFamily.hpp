#pragma once

#include <vulkan/vulkan.h>

#include <cstdint>
#include <optional>

namespace Engine
{
    namespace Core
    {
        struct Indices
        {
            std::optional<uint32_t> graphicsFamily;
            std::optional<uint32_t> presentFamily;

            bool isComplete()
            {
                return graphicsFamily.has_value() && presentFamily.has_value();
            }
        };
        
        struct QueueFamily 
        {
            static Indices find(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface);
        };
    }
}
