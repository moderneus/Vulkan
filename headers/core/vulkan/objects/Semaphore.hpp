#include "core/vulkan/objects/LogicalDevice.hpp"

#include <vulkan/vulkan.h>

struct Semaphore {
    VkSemaphore handle = VK_NULL_HANDLE;
};

VkSemaphoreCreateInfo semaphore_create_info();

void semaphore_create(Semaphore* semaphore, const LogicalDevice& device);

void semaphore_destroy(const Semaphore& semaphore, const LogicalDevice& device);
