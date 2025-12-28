#pragma once

#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "core/vulkan/objects/swapchain/Swapchain.hpp"
#include "core/vulkan/objects/renderpass/RenderPass.hpp"
#include "core/vulkan/objects/pipeline/Pipeline.hpp"
#include "core/vulkan/objects/commands/CommandPool.hpp"

#include <vulkan/vulkan.h>

struct CommandBuffer {
    VkCommandBuffer handle = VK_NULL_HANDLE;
};

VkCommandBufferBeginInfo command_buffer_create_begin_info();

void command_buffer_record(const CommandBuffer& command_buffer, const Pipeline& pipeline, const RenderPass& render_pass, const Swapchain& swapchain, uint32_t img_idx);

VkCommandBufferAllocateInfo command_buffer_create_allocate_info(const CommandPool& command_pool, const std::vector<CommandBuffer>& command_buffers);

void command_buffers_create(std::vector<CommandBuffer>* command_buffer, const LogicalDevice& device, const CommandPool& command_pool);
