#ifndef MOD_COMMAND_BUFFER_HPP
#define MOD_COMMAND_BUFFER_HPP

#include <vulkan/vulkan.h>

#include <vector>

struct device;
struct swapchain_state;
struct render_pass;
struct pipeline;
struct command_pool;
struct vertex_buffer;
struct index_buffer;

struct command_buffer {
	VkCommandBuffer handle = VK_NULL_HANDLE;
};

VkCommandBufferBeginInfo command_buffer_create_begin_info();

void command_buffer_record(const command_buffer &cmd, const pipeline &pl, const render_pass &rp, 
			   const swapchain_state &st, const vertex_buffer &buf, const index_buffer &idx_buf, const uint32_t img_idx);

VkCommandBufferAllocateInfo command_buffer_create_alloc_info(const command_pool &pool, const std::vector<command_buffer> &cmds);

void command_buffer_create(command_buffer *cmd, const device &dev, const command_pool &pool);

void command_buffers_create(std::vector<command_buffer> *cmds, const device &dev, const command_pool &pool);

#endif
