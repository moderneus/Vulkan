#include "core/vulkan/objects/Fence.hpp"
#include "util/debug/Logger.hpp"
#include "util/Constants.hpp"

VkFenceCreateInfo fence_create_info() {
    VkFenceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    create_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    return create_info;
}

void fences_create(std::vector<Fence>* fences, const LogicalDevice& device) {
    VkFenceCreateInfo fence_info = fence_create_info();
    fences->resize(MAX_FRAMES_IN_FLIGHT);
    for(uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
        if(vkCreateFence(device.handle, &fence_info, nullptr, &fences->data()[i].handle) != VK_SUCCESS) {
            log_critical("Failed to Create the Fence!");
        }
    }
}

void fences_destroy(const std::vector<Fence>& fences, const LogicalDevice& device) {
    for(uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
        if(fences[i].handle == VK_NULL_HANDLE) {
            log_error("Cannot Destroy the Fence::Fence is not Created!");
        }
        vkDestroyFence(device.handle, fences[i].handle, nullptr);
    }
}
