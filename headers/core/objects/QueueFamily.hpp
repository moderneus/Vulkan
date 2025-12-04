#pragma once

#include <vulkan/vulkan.h>

#include <cstdint>

namespace Engine
{
    namespace Core
    {
        class QueueFamily 
        {
        private:
            uint32_t indecies;

        public:
            uint32_t find(const VkPhysicalDevice& device);
        };
    }
}