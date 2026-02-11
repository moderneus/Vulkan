#include "core/vulkan/objects/commands/CommandBuffer.hpp"
#include "core/vulkan/objects/commands/CommandPool.hpp"
#include "core/vulkan/objects/renderpass/RenderPass.hpp"
#include "core/vulkan/objects/pipeline/Pipeline.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "core/vulkan/objects/buffers/types/Vertex.hpp"
#include "core/vulkan/objects/buffers/VertexBuffer.hpp"
#include "util/debug/Logger.hpp"
#include "util/Constants.hpp"

#include <array>

VkCommandBufferBeginInfo cmd_buf_create_begin_info() 
{
	VkCommandBufferBeginInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	info.flags = 0;
	info.pInheritanceInfo = nullptr;
	return info;
}

void cmd_buf_record(const command_buffer_t &cmd_buf, const pipeline_t &pipeline, const render_pass_t &rp, const swapchain_state_t &st, const vertex_buffer_t &buf, const uint32_t img_idx)
{
	VkCommandBufferBeginInfo cmd_info = cmd_buf_create_begin_info();

	if (vkBeginCommandBuffer(cmd_buf.handle, &cmd_info) != VK_SUCCESS) {
		log_critical("Failed to Begin Recording Command Buffer.");
	}

	VkClearValue clear_col = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
	VkRenderPassBeginInfo rp_info = rp_create_begin_info(rp, st, img_idx, clear_col);

	vkCmdBeginRenderPass(cmd_buf.handle, &rp_info, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(cmd_buf.handle, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.handle);
		VkViewport vp = pl_create_vp(st);
		vkCmdSetViewport(cmd_buf.handle, 0, 1, &vp);
		VkRect2D sci = pl_create_sci(st);
		vkCmdSetScissor(cmd_buf.handle, 0, 1, &sci);

		std::array<VkBuffer, 1> bufs = {buf.handle};
		std::array<VkDeviceSize, 1> offsets = {0};
		vkCmdBindVertexBuffers(cmd_buf.handle, 0, 1, bufs.data(), offsets.data());

		vkCmdDraw(cmd_buf.handle, static_cast<uint32_t>(verts.size()), 1, 0, 0);

	vkCmdEndRenderPass(cmd_buf.handle);

	if (vkEndCommandBuffer(cmd_buf.handle) != VK_SUCCESS) {
		log_critical("Failed to End Recording Command Buffer.");
	}
}

VkCommandBufferAllocateInfo cmd_buf_create_alloc_info(const command_pool_t &cmd_pool, const std::vector<command_buffer_t> &cmd_bufs)
{
	log_info("Creating Command Buffer Allocate Info...");

	VkCommandBufferAllocateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	info.commandPool = cmd_pool.handle;
	info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	info.commandBufferCount = static_cast<uint32_t>(cmd_bufs.size());

	log_info("The Command Buffer Allocate Info was Created.");

	return info;
}

void cmd_bufs_create(std::vector<command_buffer_t> *cmd_bufs, const device_t &dev, const command_pool_t &cmd_pool)
{
	log_info("Creating a Command Buffer...");

	cmd_bufs->resize(MAX_FRAMES_IN_FLIGHT);
	VkCommandBufferAllocateInfo cmd_buf_alloc_info = cmd_buf_create_alloc_info(cmd_pool, *cmd_bufs);

	if (vkAllocateCommandBuffers(dev.handle, &cmd_buf_alloc_info, &cmd_bufs->data()->handle) != VK_SUCCESS) {
		log_critical("Failed to Create the Command Buffer...");
	}

	log_info("The Command Buffer was Created.");
}
