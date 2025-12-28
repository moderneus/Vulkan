#pragma once

#include "core/vulkan/objects/instance/Instance.hpp"
#include "core/vulkan/objects/instance/Surface.hpp"
#include "core/vulkan/objects/debug/DebugMessenger.hpp"
#include "core/vulkan/objects/device/QueueFamily.hpp"
#include "core/vulkan/objects/device/Queue.hpp"
#include "core/vulkan/objects/device/PhysicalDevice.hpp" 
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "core/vulkan/objects/swapchain/Swapchain.hpp"
#include "core/vulkan/objects/pipeline/PipelineLayout.hpp"
#include "core/vulkan/objects/pipeline/Pipeline.hpp"
#include "core/vulkan/objects/renderpass/RenderPass.hpp"
#include "core/vulkan/objects/commands/CommandBuffer.hpp"
#include "core/vulkan/objects/sync/Semaphore.hpp"
#include "core/vulkan/objects/sync/Fence.hpp"

#include <vulkan/vulkan.h>

#include <vector>

struct Core {
    Instance instance;
    Surface surface;
    DebugMessenger debug_msgr;
    QueueFamily queue_family;
    Queue queue;
    PhysicalDevice phys_device;
    LogicalDevice device;
    Swapchain swapchain;
    PipelineLayout pipeline_layout;
    Pipeline pipeline;
    RenderPass render_pass;
    CommandPool command_pool;
    std::vector<CommandBuffer> command_buffers;
    std::vector<Semaphore> img_available_semaphores;
    std::vector<Semaphore> render_finished_semaphores;
    std::vector<Fence> in_flight_fences;
};

void vk_core_init(Core* vk_core, const Window& window);
void vk_core_destroy(Core* vk_core);
