#include "core/vulkan/objects/LogicalDevice.hpp"
#include "core/vulkan/objects/CommandPool.hpp"

#include <vulkan/vulkan.h>

struct CommandBuffer {
    VkCommandBuffer handle = VK_NULL_HANDLE;
};
 
VkCommandBufferAllocateInfo command_buffer_create_allocate_info(const CommandPool& command_pool);

void command_buffer_create(CommandBuffer* command_buffer, const LogicalDevice& device, const CommandPool& command_pool);
