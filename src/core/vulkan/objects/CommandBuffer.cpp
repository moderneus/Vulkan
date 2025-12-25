#include "core/vulkan/objects/CommandBuffer.hpp"
#include "util/Constants.hpp"
#include "util/debug/Logger.hpp"

VkCommandBufferBeginInfo command_buffer_create_begin_info() {
    VkCommandBufferBeginInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    create_info.flags = 0;
    create_info.pInheritanceInfo = nullptr;
    return create_info;
}

void command_buffer_record(const CommandBuffer& command_buffer, const Pipeline& pipeline, const RenderPass& render_pass, const Swapchain& swapchain, uint32_t img_idx) {
    VkCommandBufferBeginInfo command_buffer_begin_info = command_buffer_create_begin_info();
    if(vkBeginCommandBuffer(command_buffer.handle, &command_buffer_begin_info) != VK_SUCCESS) {
        log_critical("Failed to Begin Recording Command Buffer!");
    }
    VkRenderPassBeginInfo render_pass_begin_info = render_pass_create_begin_info(render_pass, swapchain, img_idx);
    vkCmdBeginRenderPass(command_buffer.handle, &render_pass_begin_info, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(command_buffer.handle, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.handle);
        VkViewport viewport = pipeline_create_viewport(swapchain);
        vkCmdSetViewport(command_buffer.handle, 0, 1, &viewport);
        VkRect2D scissor = pipeline_create_scissor(swapchain);
        vkCmdSetScissor(command_buffer.handle, 0, 1, &scissor);
        vkCmdDraw(command_buffer.handle, 3, 1, 0, 0);

    vkCmdEndRenderPass(command_buffer.handle);

    if(vkEndCommandBuffer(command_buffer.handle) != VK_SUCCESS) {
        log_critical("Failed to End Recording Command Buffer!");
    }
}

VkCommandBufferAllocateInfo command_buffer_create_allocate_info(const CommandPool& command_pool, const std::vector<CommandBuffer>& command_buffers) {
    log_info("Creating Command Buffer Allocate Info...");
    VkCommandBufferAllocateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    create_info.commandPool = command_pool.handle;
    create_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    create_info.commandBufferCount = static_cast<uint32_t>(command_buffers.size());
    log_success("The Command Buffer Allocate Info was Created!");
    return create_info;
}

void command_buffers_create(std::vector<CommandBuffer>* command_buffers, const LogicalDevice& device, const CommandPool& command_pool) {
    log_info("Creating a Command Buffer...");
    command_buffers->resize(MAX_FRAMES_IN_FLIGHT);
    VkCommandBufferAllocateInfo command_buffer_allocate_info = command_buffer_create_allocate_info(command_pool, *command_buffers);
    if(vkAllocateCommandBuffers(device.handle, &command_buffer_allocate_info, &command_buffers->data()->handle) != VK_SUCCESS) {
        log_critical("Failed to Create the Command Buffer...");
    }
    log_success("The Command Buffer was Created!");
}
