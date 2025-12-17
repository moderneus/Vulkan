#pragma once

#include "core/vulkan/objects/Instance.hpp"
#include "core/vulkan/objects/PhysicalDevice.hpp"
#include "core/vulkan/objects/LogicalDevice.hpp"
#include "core/vulkan/objects/Surface.hpp"
#include "core/vulkan/objects/Swapchain.hpp"
#include "core/vulkan/objects/ImageView.hpp"
#include "core/vulkan/objects/PipelineLayout.hpp"
#include "core/vulkan/objects/Pipeline.hpp"
#include "core/vulkan/objects/RenderPass.hpp"
#include "util/debug/ValidationLayers.hpp"

#include <vulkan/vulkan.h>

struct Core {
    Instance instance;
    DebugMessenger debug_msgr;
    PhysicalDevice phys_device;
    LogicalDevice device;
    Surface surface;
    Swapchain swapchain;
    ImageView image_view;
    PipelineLayout pipeline_layout;
    Pipeline pipeline;
    RenderPass render_pass;
};

void vk_core_init(Core* vk_core, const Window& window);
void vk_core_destroy(Core* vk_core);
