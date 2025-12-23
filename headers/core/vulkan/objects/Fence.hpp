#include "core/vulkan/objects/LogicalDevice.hpp" 

#include <vulkan/vulkan.h>

struct Fence {
    VkFence handle = VK_NULL_HANDLE;
};

VkFenceCreateInfo fence_create_info();

void fence_create(Fence* fence, const LogicalDevice& device);

void fence_destroy(const Fence& fence, const LogicalDevice& device);
