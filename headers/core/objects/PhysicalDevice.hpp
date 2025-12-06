#pragma once

#include "core/objects/Surface.hpp"

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

namespace Engine
{
    namespace Core
    {
        const std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

        class PhysicalDevice
        {
        private:
            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

            int rate(const VkPhysicalDevice& device);
            std::string name(const VkPhysicalDevice& device);
            bool checkExtensionSupport(const VkPhysicalDevice& device);
            bool isSuitable(const VkPhysicalDevice& device, const VkSurfaceKHR& surface);

        public:
            void pick(const Surface& surface);

            VkPhysicalDeviceFeatures features();
            VkPhysicalDevice get() const;
        };
    }
}

