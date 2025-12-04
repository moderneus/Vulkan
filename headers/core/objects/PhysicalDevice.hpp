#pragma once

#include <vulkan/vulkan.h>

#include <string>
#include <vulkan/vulkan_core.h>

namespace Engine
{
    namespace Core
    {
        class PhysicalDevice
        {
        private:
            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

            int rate(const VkPhysicalDevice& device);
            std::string name(const VkPhysicalDevice& device);
            bool isSuitable(const VkPhysicalDevice& device);

        public:
            void pick();

            VkPhysicalDeviceFeatures features();
            VkPhysicalDevice get() const;
        };
    }
}

