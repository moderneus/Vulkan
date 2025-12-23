#include "core/vulkan/objects/Fence.hpp"
#include "util/debug/Logger.hpp"

VkFenceCreateInfo fence_create_info() {
    VkFenceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    return create_info;
}

void fence_create(Fence* fence, const LogicalDevice& device) {
    VkFenceCreateInfo fence_info = fence_create_info();
    if(vkCreateFence(device.handle, &fence_info, nullptr, &fence->handle) != VK_SUCCESS) {
        log_critical("Failed to Create the Fence!");
    }
}

void fence_destroy(const Fence& fence, const LogicalDevice& device) {
    if(fence.handle == VK_NULL_HANDLE) {
        log_error("Cannot Destroy the Fence::Fence is not Created!");
    }
    vkDestroyFence(device.handle, fence.handle, nullptr);
}
