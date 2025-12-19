#pragma once

#include "core/vulkan/objects/LogicalDevice.hpp"
#include "core/vulkan/objects/Swapchain.hpp"

#include <vulkan/vulkan.h>

VkImageViewCreateInfo image_view_create_info(const VkImage& image, const VkFormat& format);

void image_view_create(Swapchain* swapchain, const LogicalDevice& device);

void image_view_destroy(const Swapchain& swapchain, const LogicalDevice& device);
