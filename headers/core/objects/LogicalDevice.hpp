#pragma once

#include "core/objects/PhysicalDevice.hpp"
#include "core/objects/Surface.hpp"

#include <vulkan/vulkan.h>

namespace Engine 
{
    namespace Core
    {
        class LogicalDevice
        {
        private:
            VkDevice device = VK_NULL_HANDLE;

            VkDeviceQueueCreateInfo createQueueInfo(const PhysicalDevice& physicalDevice, const Surface& surface);
            VkDeviceCreateInfo createInfo(PhysicalDevice& physicalDevice, const VkDeviceQueueCreateInfo& queueInfo, VkPhysicalDeviceFeatures* physicalDeviceFeatures);

        public:
            void create(PhysicalDevice& physicalDevice, const Surface& surface);
            void destroy();

            VkDevice get() const;
        };
    }
}
