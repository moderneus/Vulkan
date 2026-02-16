#ifndef MOD_COMMAND_POOL_HPP
#define MOD_COMMAND_POOL_HPP

#include <vulkan/vulkan.h>

struct queue_indices;
struct device;

struct command_pool
{
	VkCommandPool handle = VK_NULL_HANDLE;
};

VkCommandPoolCreateInfo command_pool_create_info(const queue_indices &q_idx);

void command_pool_create(command_pool *pool, const device &dev, const queue_indices &q_idx);

void command_pool_destroy(const command_pool &pool, const device &dev);

#endif
