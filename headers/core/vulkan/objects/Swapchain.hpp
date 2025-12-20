#pragma once

#include "core/vulkan/objects/PhysicalDevice.hpp"
#include "core/vulkan/objects/LogicalDevice.hpp"
#include "core/vulkan/objects/Surface.hpp"

#include <vulkan/vulkan.h>

#include <vector>

struct SwapchainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> present_modes;
};

struct Swapchain {
    VkSwapchainKHR handle = VK_NULL_HANDLE;
    VkExtent2D extent = {};
    VkFormat format = VK_FORMAT_UNDEFINED;
    VkColorSpaceKHR color_space = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    std::vector<VkFramebuffer> frame_buffers;
    std::vector<VkImageView> views; 
    std::vector<VkImage> images;
};

SwapchainSupportDetails swapchain_query_support_details(const VkPhysicalDevice& phys_device, const VkSurfaceKHR& surface);

VkSurfaceFormatKHR swapchain_choose_format(const std::vector<VkSurfaceFormatKHR>& formats);

VkPresentModeKHR swapchain_choose_present_mode(const std::vector<VkPresentModeKHR>& present_modes);

VkExtent2D swapchain_choose_extent(const Window& window, const VkSurfaceCapabilitiesKHR& capabilities);

VkSwapchainCreateInfoKHR swapchain_create_info(
        const VkSurfaceKHR& surface, 
        const VkPhysicalDevice& phys_device, 
        const VkSurfaceFormatKHR& format, 
        const VkPresentModeKHR& present_mode, 
        const VkExtent2D& extent, 
        const VkSurfaceCapabilitiesKHR& capabilities, 
        uint32_t image_count
);

bool swapchain_is_adequate(const VkPhysicalDevice& phys_device, const VkSurfaceKHR& surface);

void swapchain_create(Swapchain* swapchain, const PhysicalDevice& phys_device, const LogicalDevice& device, const Window& window, const Surface& surface);

void swapchain_destroy(const Swapchain& swapchain, const LogicalDevice& device);
