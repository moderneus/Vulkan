#include "core/vulkan/obj/command/command_buffer.hpp"
#include "core/vulkan/obj/command/command_pool.hpp"
#include "core/vulkan/obj/renderpass/render_pass.hpp"
#include "core/vulkan/obj/pipeline/pipeline.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "core/vulkan/obj/buffer/vertex.hpp"
#include "core/vulkan/obj/buffer/vertex_buffer.hpp"
#include "core/vulkan/obj/buffer/index_buffer.hpp"
#include "util/debug/log.hpp"
#include "util/constants.hpp"

#include <array>

VkCommandBufferBeginInfo command_buffer_create_begin_info() 
{
	VkCommandBufferBeginInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	info.flags = 0;
	info.pInheritanceInfo = nullptr;
	return info;
}

void command_buffer_record(const command_buffer &cmd, const pipeline &pl, const render_pass &rp, 
			   const swapchain_state &st, const vertex_buffer &buf, const index_buffer &idx_buf, const uint32_t img_idx)
{
	VkCommandBufferBeginInfo cmd_begin = command_buffer_create_begin_info();

	if (vkBeginCommandBuffer(cmd.handle, &cmd_begin) != VK_SUCCESS)
		log_critical("Failed to Begin Recording Command Buffer.");

	VkClearValue clear_col = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
	VkRenderPassBeginInfo rp_begin = render_pass_create_begin_info(rp, st, clear_col, img_idx);

	vkCmdBeginRenderPass(cmd.handle, &rp_begin, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(cmd.handle, VK_PIPELINE_BIND_POINT_GRAPHICS, pl.handle);
		VkViewport vp = pipeline_create_viewport(st);
		vkCmdSetViewport(cmd.handle, 0, 1, &vp);
		VkRect2D sc = pipeline_create_scissor(st);
		vkCmdSetScissor(cmd.handle, 0, 1, &sc);

		std::array<VkBuffer, 1> bufs = {buf.vbuf.handle};
		std::array<VkDeviceSize, 1> offsets = {0};

		vkCmdBindVertexBuffers(cmd.handle, 0, 1, bufs.data(), offsets.data());
		vkCmdBindIndexBuffer(cmd.handle, idx_buf.ibuf.handle, 0, VK_INDEX_TYPE_UINT32);

		vkCmdDrawIndexed(cmd.handle, static_cast<uint32_t>(rectangle_indices.size()), 1, 0, 0, 0);

	vkCmdEndRenderPass(cmd.handle);

	if (vkEndCommandBuffer(cmd.handle) != VK_SUCCESS)
		log_critical("Failed to End Recording Command Buffer.");
}

VkCommandBufferAllocateInfo command_buffer_create_alloc_info(const command_pool &pool, const std::vector<command_buffer> &cmds)
{
	log_info("Creating Command Buffer Allocate Info...");

	VkCommandBufferAllocateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	info.commandPool = pool.handle;
	info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	info.commandBufferCount = static_cast<uint32_t>(cmds.size());

	log_info("The Command Buffer Allocate Info was Created.");

	return info;
}

void command_buffers_create(std::vector<command_buffer> *cmds, const device &dev, const command_pool &pool)
{
	log_info("Creating a Command Buffer...");

	cmds->resize(MAX_FRAMES_IN_FLIGHT);

	for(uint32_t i = 0; i < cmds->size(); ++i) {
		VkCommandBufferAllocateInfo info = command_buffer_create_alloc_info(pool, *cmds);

		if (vkAllocateCommandBuffers(dev.handle, &info, &cmds->data()[i].handle) != VK_SUCCESS)
			log_critical("Failed to Create the Command Buffer...");
	}

	log_info("The Command Buffer was Created.");
}
