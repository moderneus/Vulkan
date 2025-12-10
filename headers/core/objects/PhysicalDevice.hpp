#pragma once

#include "core/objects/Surface.hpp"

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

namespace Engine
{
    namespace Core
    {
        const std::vector<const char*> physicalDeviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

        class PhysicalDevice
        {
        private:
            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

            int rate(const VkPhysicalDevice& physicalDevice);
            std::string name(const VkPhysicalDevice& physicalDevice);
            bool checkExtensionSupport(const VkPhysicalDevice& physicalDevice);
            bool isSuitable(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface);

        public:
            void pick(const Surface& surface);

            VkPhysicalDeviceFeatures features();
            VkPhysicalDevice get() const;
        };
    }
}

