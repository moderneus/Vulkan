#include "core/vulkan/objects/commands/CommandBuffer.hpp"
#include "core/vulkan/objects/commands/CommandPool.hpp"
#include "core/vulkan/objects/renderpass/RenderPass.hpp"
#include "core/vulkan/objects/pipeline/Pipeline.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "util/debug/Logger.hpp"
#include "util/Constants.hpp"

VkCommandBufferBeginInfo command_buffer_create_begin_info() 
{
	VkCommandBufferBeginInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	create_info.flags = 0;
	create_info.pInheritanceInfo = nullptr;
	return create_info;
}

void command_buffer_record(const command_buffer_t& command_buffer, const pipeline_t& pipeline, const render_pass_t& render_pass, const swapchain_t& swapchain, const uint32_t img_idx) 
{
	VkCommandBufferBeginInfo command_buffer_begin_info = command_buffer_create_begin_info();

	if (vkBeginCommandBuffer(command_buffer.handle, &command_buffer_begin_info) != VK_SUCCESS) {
		log_critical("Failed to Begin Recording Command Buffer!");
	}

	VkClearValue clear_color = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
	VkRenderPassBeginInfo render_pass_begin_info = render_pass_create_begin_info(render_pass, swapchain, img_idx, clear_color);

	vkCmdBeginRenderPass(command_buffer.handle, &render_pass_begin_info, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(command_buffer.handle, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.handle);
		VkViewport viewport = pipeline_create_viewport(swapchain);
		vkCmdSetViewport(command_buffer.handle, 0, 1, &viewport);
		VkRect2D scissor = pipeline_create_scissor(swapchain);
		vkCmdSetScissor(command_buffer.handle, 0, 1, &scissor);
		vkCmdDraw(command_buffer.handle, 3, 1, 0, 0);

	vkCmdEndRenderPass(command_buffer.handle);

	if (vkEndCommandBuffer(command_buffer.handle) != VK_SUCCESS) {
		log_critical("Failed to End Recording Command Buffer!");
	}
}

VkCommandBufferAllocateInfo command_buffer_create_allocate_info(const command_pool_t& command_pool, const std::vector<command_buffer_t>& command_buffers)
{
	log_info("Creating Command Buffer Allocate Info...");

	VkCommandBufferAllocateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	create_info.commandPool = command_pool.handle;
	create_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	create_info.commandBufferCount = static_cast<uint32_t>(command_buffers.size());

	log_success("The Command Buffer Allocate Info was Created!");

	return create_info;
}

void command_buffers_create(std::vector<command_buffer_t>* command_buffers, const device_t& device, const command_pool_t& command_pool)
{
	log_info("Creating a Command Buffer...");

	command_buffers->resize(MAX_FRAMES_IN_FLIGHT);
	VkCommandBufferAllocateInfo command_buffer_allocate_info = command_buffer_create_allocate_info(command_pool, *command_buffers);
	if (vkAllocateCommandBuffers(device.handle, &command_buffer_allocate_info, &command_buffers->data()->handle) != VK_SUCCESS) {
		log_critical("Failed to Create the Command Buffer...");
	}

	log_success("The Command Buffer was Created!");
}
