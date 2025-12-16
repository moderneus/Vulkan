#pragma once

#include "core/objects/LogicalDevice.hpp"

#include <vulkan/vulkan.h>

struct PipelineLayout {
    VkPipelineLayout handle = VK_NULL_HANDLE;
};

VkPipelineLayoutCreateInfo pipeline_layout_create_info();

void pipeline_layout_create(PipelineLayout* pipeline_layout, const LogicalDevice& device);

void pipeline_layout_destroy(const PipelineLayout& pipeline_layout, const LogicalDevice& device);
