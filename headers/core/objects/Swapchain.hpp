#pragma once

#include "core/objects/PhysicalDevice.hpp"
#include "core/objects/LogicalDevice.hpp"
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

            VkExtent2D actualExtent;
            
            static SwapchainSupportDetails querySupportDetails(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface);
            VkSurfaceFormatKHR chooseFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
            VkPresentModeKHR choosePresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
            VkExtent2D chooseExtent(const VkSurfaceCapabilitiesKHR& capabilities);
            VkSwapchainCreateInfoKHR createInfo
            (
                const VkSurfaceKHR& surface, 
                const VkPhysicalDevice& device, 
                const VkSurfaceFormatKHR& format, 
                const VkPresentModeKHR& presentMode, 
                const VkExtent2D& extent, 
                const VkSurfaceCapabilitiesKHR& capabilities, 
                const uint32_t imageCount
            );

        public:
            static bool isAdequate(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface);

            void create(const PhysicalDevice& physicalDevice, const LogicalDevice& device, const Surface& surface);
            void destroy(const LogicalDevice& device);

            VkExtent2D extent() const;
            VkSwapchainKHR get() const;
        };
    }
}
