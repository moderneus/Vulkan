#pragma once

#include "core/objects/PhysicalDevice.hpp"
#include "core/objects/Surface.hpp"

#include <vulkan/vulkan.h>

#include <vector>

namespace Engine 
{
    namespace Core
    {
        struct SwapchainSupportDetails
        {
            VkSurfaceCapabilitiesKHR capabilities;
            std::vector<VkSurfaceFormatKHR> formats;
            std::vector<VkPresentModeKHR> presentModes;
        };

        class Swapchain
        {
        private:
            VkSwapchainKHR swapchain = VK_NULL_HANDLE;
            
            static SwapchainSupportDetails querySupportDetails(const VkPhysicalDevice& device, const VkSurfaceKHR& surface);
            VkSurfaceFormatKHR chooseFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
            VkSurfacePresentModeKHR choosePresentMode(const std::vector<VkSurfacePresentModeKHR>& availablePresentModes);

        public:
            static bool isAdequate(const VkPhysicalDevice& device, const VkSurfaceKHR& surface);

            void create(const PhysicalDevice& device, const Surface& surface);
            void destroy();

            VkSwapchainKHR get() const;
        };
    }
}