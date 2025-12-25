#pragma once

#include "core/vulkan/objects/LogicalDevice.hpp" 

#include <vulkan/vulkan.h>

#include <vector>

struct Fence {
    VkFence handle = VK_NULL_HANDLE;
};

VkFenceCreateInfo fence_create_info();

void fences_create(std::vector<Fence>* fences, const LogicalDevice& device);

void fences_destroy(const std::vector<Fence>& fences, const LogicalDevice& device);
