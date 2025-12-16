#pragma once

#include "core/objects/Instance.hpp"
#include "core/objects/PhysicalDevice.hpp"
#include "core/objects/LogicalDevice.hpp"
#include "core/objects/Surface.hpp"
#include "core/objects/Swapchain.hpp"
#include "core/objects/ImageView.hpp"
#include "core/objects/PipelineLayout.hpp"
#include "core/objects/Pipeline.hpp"

#include <vulkan/vulkan.h>

struct Core {
    Instance instance;
    PhysicalDevice phys_device;
    LogicalDevice device;
    Surface surface;
    Swapchain swapchain;
    ImageView image_view;
    PipelineLayout pipeline_layout;
    Pipeline pipeline;
};

void vk_core_init();
void vk_core_destroy();
