#pragma once

#include "core/vulkan/objects/LogicalDevice.hpp"
#include "core/vulkan/objects/Swapchain.hpp"

#include <vulkan/vulkan.h>

VkImageViewCreateInfo img_view_create_info(const VkImage& img, const VkFormat& format);

void img_view_create(Swapchain* swapchain, const LogicalDevice& device);

void img_view_destroy(const Swapchain& swapchain, const LogicalDevice& device);
