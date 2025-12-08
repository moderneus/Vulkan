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
        
        class QueueFamily 
        {
        private:

        public:
            Indices find(const VkPhysicalDevice& device, const VkSurfaceKHR& surface);
        };
    }
}