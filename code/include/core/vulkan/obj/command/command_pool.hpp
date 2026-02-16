#ifndef MOD_CMD_POOL_HPP
#define MOD_CMD_POOL_HPP

#include <vulkan/vulkan.h>

struct queue_family_t;
struct device_t;

struct command_pool_t
{
	VkCommandPool handle = VK_NULL_HANDLE;
};

VkCommandPoolCreateInfo cmd_pool_create_info(const queue_family_t &qf);

void cmd_pool_create(command_pool_t *cmd_pool, const device_t &dev, const queue_family_t &qf);

void cmd_pool_destroy(const command_pool_t &cmd_pool, const device_t &dev);

#endif
