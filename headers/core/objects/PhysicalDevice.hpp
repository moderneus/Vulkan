#pragma once

#include <vulkan/vulkan.h>

namespace Engine
{
    namespace Core
    {
        class PhysicalDevice
        {
        private:
            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

            int ratePhysicalDevice(const VkPhysicalDevice& device);

        public:
            void pick();

            VkPhysicalDevice get();
        };
    }
}

