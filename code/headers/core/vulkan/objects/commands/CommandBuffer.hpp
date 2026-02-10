#ifndef MOD_COMMAND_BUFFER_HPP
#define MOD_COMMAND_BUFFER_HPP

#include <vulkan/vulkan.h>

#include <vector>

struct device_t;
struct swapchain_state_t;
struct render_pass_t;
struct pipeline_t;
struct command_pool_t;
struct vertex_buffer_t;

struct command_buffer_t
{
	VkCommandBuffer handle = VK_NULL_HANDLE;
};

VkCommandBufferBeginInfo cmd_buf_create_begin_info();

void cmd_buf_record(const command_buffer_t &cmd_buf, const pipeline_t &pipeline, const render_pass_t &rp, const swapchain_state_t &st, const vertex_buffer_t &buf, const uint32_t img_idx);

VkCommandBufferAllocateInfo cmd_buf_create_alloc_info(const command_pool_t &cmd_pool, const std::vector<command_buffer_t> &cmd_bufs);

void cmd_bufs_create(std::vector<command_buffer_t> *cmd_buf, const device_t &dev, const command_pool_t &cmd_pool);

#endif
