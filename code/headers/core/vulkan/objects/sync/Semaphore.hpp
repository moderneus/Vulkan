#pragma once

#include <vulkan/vulkan.h>

#include <vector>

struct LogicalDevice;

struct Semaphore {
    VkSemaphore handle = VK_NULL_HANDLE;
};

VkSemaphoreCreateInfo semaphore_create_info();

void semaphores_create(std::vector<Semaphore>* semaphores, const LogicalDevice& device);

void semaphores_destroy(const std::vector<Semaphore>& semaphores, const LogicalDevice& device);
