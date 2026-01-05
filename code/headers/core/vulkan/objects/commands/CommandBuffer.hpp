#pragma once

#include <vulkan/vulkan.h>

#include <vector>

struct LogicalDevice;
struct Swapchain;
struct RenderPass;
struct Pipeline;
struct CommandPool;

struct CommandBuffer {
    VkCommandBuffer handle = VK_NULL_HANDLE;
};

VkCommandBufferBeginInfo command_buffer_create_begin_info();

void command_buffer_record(const CommandBuffer& command_buffer, const Pipeline& pipeline, const RenderPass& render_pass, const Swapchain& swapchain, const uint32_t img_idx);

VkCommandBufferAllocateInfo command_buffer_create_allocate_info(const CommandPool& command_pool, const std::vector<CommandBuffer>& command_buffers);

void command_buffers_create(std::vector<CommandBuffer>* command_buffer, const LogicalDevice& device, const CommandPool& command_pool);
