#pragma once

#include <vulkan/vulkan.h>

struct LogicalDevice;
struct Swapchain;

VkImageViewCreateInfo img_view_create_info(const VkImage& img, const VkFormat& format);

void img_view_create(Swapchain* swapchain, const LogicalDevice& device);

void img_view_destroy(const Swapchain& swapchain, const LogicalDevice& device);
