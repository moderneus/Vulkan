#include "core/vulkan/obj/command/command_pool.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "core/vulkan/obj/device/queue_indices.hpp"
#include "util/debug/log.hpp"

VkCommandPoolCreateInfo command_pool_create_info(const queue_indices &q_idx) 
{
	log_info("Creating the Command Pool Info...");

	VkCommandPoolCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	info.queueFamilyIndex = q_idx.gfx.value();

	log_info("The Command Pool Info was Created.");

	return info;
}

void command_pool_create(command_pool *pool, const device &dev, const queue_indices &q_idx) 
{
	log_info("Creating a Command Pool...");

	VkCommandPoolCreateInfo info = command_pool_create_info(q_idx);

	if (vkCreateCommandPool(dev.handle, &info, nullptr, &pool->handle) != VK_SUCCESS)
		log_critical("Failed to Create the Command Pool.");

	log_info("The Command Pool was Created.");
}

void command_pool_destroy(const command_pool &pool, const device &dev) 
{
	log_info("Destroying the Command Pool...");

	if (pool.handle == VK_NULL_HANDLE)
		log_error("Cannot Destroy the Command Pool::Command Pool is not Created.");

	vkDestroyCommandPool(dev.handle, pool.handle, nullptr);

	log_info("The Command Pool was Destroyed.");
}
