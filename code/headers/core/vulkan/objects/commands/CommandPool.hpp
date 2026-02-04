#ifndef MOD_COMMAND_POOL_HPP
#define MOD_COMMAND_POOL_HPP

#include <vulkan/vulkan.h>

struct queue_family_t;
struct device_t;

struct command_pool_t
{
	VkCommandPool handle = VK_NULL_HANDLE;
};

VkCommandPoolCreateInfo command_pool_create_info(const queue_family_t& queue_family);

void command_pool_create(command_pool_t* command_pool, const device_t& device, const queue_family_t& queue_family);

void command_pool_destroy(const command_pool_t& command_pool, const device_t& device);

#endif
