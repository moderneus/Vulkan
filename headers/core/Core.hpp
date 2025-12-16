#pragma once

#include "core/objects/Instance.hpp"
#include "core/objects/PhysicalDevice.hpp"
#include "core/objects/LogicalDevice.hpp"
#include "core/objects/Surface.hpp"
#include "core/objects/Swapchain.hpp"
#include "core/objects/ImageView.hpp"
#include "core/objects/PipelineLayout.hpp"
#include "core/objects/Pipeline.hpp"
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
};

void vk_core_init(Core* vk_core, const Window& window);
void vk_core_destroy(Core* vk_core);
