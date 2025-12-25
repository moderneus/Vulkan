#include "core/vulkan/objects/Semaphore.hpp"
#include "util/debug/Logger.hpp"
#include "util/Constants.hpp"

VkSemaphoreCreateInfo semaphore_create_info() {
    VkSemaphoreCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    return create_info;
}

void semaphores_create(std::vector<Semaphore>* semaphores, const LogicalDevice& device) {
    VkSemaphoreCreateInfo semaphore_info = semaphore_create_info();
    semaphores->resize(MAX_FRAMES_IN_FLIGHT);
    for(uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
        if(vkCreateSemaphore(device.handle, &semaphore_info, nullptr, &semaphores->data()[i].handle) != VK_SUCCESS) {
            log_critical("Failed to Create the Semaphore!");
        }
    }
}

void semaphores_destroy(const std::vector<Semaphore>& semaphores, const LogicalDevice& device) {
    for(uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
        if(semaphores[i].handle == VK_NULL_HANDLE) {
            log_error("Cannot Destroy the Semaphore::Semaphore is not Created!");
        }
        vkDestroySemaphore(device.handle, semaphores[i].handle, nullptr);
    }
}
