#pragma once

#include "core/objects/PhysicalDevice.hpp"

#include <vulkan/vulkan.h>

namespace Engine 
{
    namespace Core
    {
        class LogicalDevice
        {
        private:
            VkDevice logicalDevice = VK_NULL_HANDLE;

            VkDeviceQueueCreateInfo createQueueInfo(const PhysicalDevice& device);
            VkDeviceCreateInfo createInfo(PhysicalDevice& device, const VkDeviceQueueCreateInfo& queueInfo, VkPhysicalDeviceFeatures* deviceFeatures);

        public:
            void create(PhysicalDevice& device);
            void destroy();

            VkDevice get() const;
        };
    }
}