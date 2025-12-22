#include "core/vulkan/objects/CommandBuffer.hpp"
#include "util/debug/Logger.hpp"

VkCommandBufferAllocateInfo command_buffer_create_allocate_info(const CommandPool& command_pool) {
    log_info("Creating Command Buffer Allocate Info...");
    VkCommandBufferAllocateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    create_info.commandPool = command_pool.handle;
    create_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    create_info.commandBufferCount = 1;
    log_success("The Command Buffer Allocate Info was Created!");
    return create_info;
}

void command_buffer_create(CommandBuffer* command_buffer, const LogicalDevice& device, const CommandPool& command_pool) {
    log_info("Creating a Command Buffer...");
    VkCommandBufferAllocateInfo command_buffer_allocate_info = command_buffer_create_allocate_info(command_pool);
    if(vkAllocateCommandBuffers(device.handle, &command_buffer_allocate_info, &command_buffer->handle) != VK_SUCCESS) {
        log_critical("Failed to Create the Command Buffer...");
    }
    log_success("The Command Buffer was Created!");
}
