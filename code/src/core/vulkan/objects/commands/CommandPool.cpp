#include "core/vulkan/objects/commands/CommandPool.hpp"
#include "core/vulkan/objects/device/QueueFamily.hpp"
#include "util/debug/Logger.hpp"

VkCommandPoolCreateInfo command_pool_create_info(const QueueFamily& queue_family) {
    log_info("Creating the Command Pool Info...");
    VkCommandPoolCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    create_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    create_info.queueFamilyIndex = queue_family.graphics.value();
    log_success("The Command Pool Info was Created!");
    return create_info;
}

void command_pool_create(CommandPool* command_pool, const LogicalDevice& device, const QueueFamily& queue_family) {
    log_info("Creating a Command Pool...");
    VkCommandPoolCreateInfo command_pool_info = command_pool_create_info(queue_family);
    if(vkCreateCommandPool(device.handle, &command_pool_info, nullptr, &command_pool->handle) != VK_SUCCESS) {
        log_critical("Failed to Create the Command Pool!");
    }
    log_success("The Command Pool was Created!");
}

void command_pool_destroy(const CommandPool& command_pool, const LogicalDevice& device) {
    log_info("Destroying the Command Pool...");
    if(command_pool.handle == VK_NULL_HANDLE) {
        log_error("Cannot Destroy the Command Pool::Command Pool is not Created!");
    }
    vkDestroyCommandPool(device.handle, command_pool.handle, nullptr);
    log_success("The Command Pool was Destroyed!");
}
