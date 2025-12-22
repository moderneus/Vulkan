#include "core/vulkan/objects/LogicalDevice.hpp"
#include "core/vulkan/objects/Swapchain.hpp"
#include "core/vulkan/objects/RenderPass.hpp"
#include "core/vulkan/objects/Pipeline.hpp"
#include "core/vulkan/objects/CommandPool.hpp"

#include <vulkan/vulkan.h>

struct CommandBuffer {
    VkCommandBuffer handle = VK_NULL_HANDLE;
};

VkCommandBufferBeginInfo command_buffer_create_begin_info();

void command_buffer_record(const CommandBuffer& command_buffer, const Pipeline& pipeline, const RenderPass& render_pass, const Swapchain& swapchain, uint32_t img_idx);
 
VkCommandBufferAllocateInfo command_buffer_create_allocate_info(const CommandPool& command_pool);

void command_buffer_create(CommandBuffer* command_buffer, const LogicalDevice& device, const CommandPool& command_pool);
