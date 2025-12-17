#pragma once

#include "core/vulkan/objects/LogicalDevice.hpp"

#include <vulkan/vulkan.h>

#include <vector>

struct ImageView {
    VkImageView handle = VK_NULL_HANDLE;
    std::vector<VkImageView> views; 
    std::vector<VkImage> images;
    VkFormat format;
};

void image_view_create(ImageView* image_view, const LogicalDevice& device);

void image_view_destroy(const ImageView& image_view, const LogicalDevice& device);
