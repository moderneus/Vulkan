#include "core/vulkan/objects/LogicalDevice.hpp"

#include <vulkan/vulkan.h>

struct CommandPool {
    VkCommandPool handle = VK_NULL_HANDLE;
};

VkCommandPoolCreateInfo command_pool_create_info(const PhysicalDevice& phys_device, const Surface& surface);

void command_pool_create(CommandPool* command_pool, const LogicalDevice& device, const PhysicalDevice& phys_device, const Surface& surface);

void command_pool_destroy(const CommandPool& command_pool, const LogicalDevice& device);
