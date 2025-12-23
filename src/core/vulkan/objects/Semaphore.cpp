#include "core/vulkan/objects/Semaphore.hpp"
#include "util/debug/Logger.hpp"

VkSemaphoreCreateInfo semaphore_create_info() {
    VkSemaphoreCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    return create_info;
}

void semaphore_create(Semaphore* semaphore, const LogicalDevice& device) {
    VkSemaphoreCreateInfo semaphore_info = semaphore_create_info();
    if(vkCreateSemaphore(device.handle, &semaphore_info, nullptr, &semaphore->handle) != VK_SUCCESS) {
        log_critical("Failed to Create the Semaphore!");
    }
}

void semaphore_destroy(const Semaphore& semaphore, const LogicalDevice& device) {
    if(semaphore.handle == VK_NULL_HANDLE) {
        log_error("Cannot Destroy the Semaphore::Semaphore is not Created!");
    }
    vkDestroySemaphore(device.handle, semaphore.handle, nullptr);
}
