#include "core/vulkan/objects/commands/CommandPool.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "core/vulkan/objects/device/QueueFamily.hpp"
#include "util/debug/Logger.hpp"

VkCommandPoolCreateInfo cmd_pool_create_info(const queue_family_t &qf) 
{
	log_info("Creating the Command Pool Info...");

	VkCommandPoolCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	info.queueFamilyIndex = qf.gfx.value();

	log_info("The Command Pool Info was Created.");

	return info;
}

void cmd_pool_create(command_pool_t *cmd_pool, const device_t &dev, const queue_family_t &qf) 
{
	log_info("Creating a Command Pool...");

	VkCommandPoolCreateInfo cmd_pool_info = cmd_pool_create_info(qf);

	if (vkCreateCommandPool(dev.handle, &cmd_pool_info, nullptr, &cmd_pool->handle) != VK_SUCCESS) {
		log_critical("Failed to Create the Command Pool.");
	}

	log_info("The Command Pool was Created.");
}

void cmd_pool_destroy(const command_pool_t &cmd_pool, const device_t &dev) 
{
	log_info("Destroying the Command Pool...");

	if (cmd_pool.handle == VK_NULL_HANDLE) {
		log_error("Cannot Destroy the Command Pool::Command Pool is not Created.");
	}
	vkDestroyCommandPool(dev.handle, cmd_pool.handle, nullptr);

	log_info("The Command Pool was Destroyed.");
}
