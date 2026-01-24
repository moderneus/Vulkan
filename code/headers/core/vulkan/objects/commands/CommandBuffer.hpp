#ifndef MOD_COMMAND_BUFFER_HPP
#define MOD_COMMAND_BUFFER_HPP

#include <vulkan/vulkan.h>

#include <vector>

struct device_t;
struct swapchain_t;
struct render_pass_t;
struct pipeline_t;
struct command_pool_t;

struct command_buffer_t
{
	VkCommandBuffer handle = VK_NULL_HANDLE;
};

VkCommandBufferBeginInfo command_buffer_create_begin_info();

void command_buffer_record(const command_buffer_t& command_buffer, const pipeline_t& pipeline, const render_pass_t& render_pass, const swapchain_t& swapchain, const uint32_t img_idx);

VkCommandBufferAllocateInfo command_buffer_create_allocate_info(const command_pool_t& command_pool, const std::vector<command_buffer_t>& command_buffers);

void command_buffers_create(std::vector<command_buffer_t>* command_buffer, const device_t& device, const command_pool_t& command_pool);

#endif
