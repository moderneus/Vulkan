#pragma once

#include "core/vulkan/objects/device/LogicalDevice.hpp"

#include <vulkan/vulkan.h>

struct Semaphore {
    VkSemaphore handle = VK_NULL_HANDLE;
};

VkSemaphoreCreateInfo semaphore_create_info();

void semaphores_create(std::vector<Semaphore>* semaphores, const LogicalDevice& device);

void semaphores_destroy(const std::vector<Semaphore>& semaphores, const LogicalDevice& device);
