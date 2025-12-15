#pragma once

#include "core/objects/LogicalDevice.hpp"
#include "core/objects/ShaderModule.hpp"
#include "core/objects/Swapchain.hpp"

#include <vulkan/vulkan.h>

#include <array>

struct Pipeline {
    VkPipeline handle = VK_NULL_HANDLE;
    ShaderModule vertexShader;
    ShaderModule fragmentShader;
};

struct PipelineState {
    std::array<VkPipelineShaderStageCreateInfo, 2> shaderStages = {};
    VkPipelineDynamicStateCreateInfo dynamicStateInfo = {};
    VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo = {};
    VkPipelineViewportStateCreateInfo viewportInfo = {};
    VkPipelineRasterizationStateCreateInfo rasterizationInfo = {};
    VkPipelineMultisampleStateCreateInfo multisampleInfo = {};
    VkPipelineDepthStencilStateCreateInfo depthStencilInfo = {};
    VkPipelineColorBlendStateCreateInfo colorBlendInfo = {};
};

VkViewport pipeline_create_viewport(const Swapchain& swapchain);

VkRect2D pipeline_create_scissor(const Swapchain& swapchain);

void pipeline_create_shader_modules(const LogicalDevice& device);

std::array<VkPipelineShaderStageCreateInfo, 2> pipeline_create_shader_stage_info();

VkPipelineDynamicStateCreateInfo pipeline_create_dynamic_state_info();

VkPipelineVertexInputStateCreateInfo pipeline_create_vertex_input_info();

VkPipelineInputAssemblyStateCreateInfo pipeline_create_input_assembly_info();

VkPipelineViewportStateCreateInfo pipeline_create_viewport_info(const VkViewport& viewport, const VkRect2D& scissor);

VkPipelineRasterizationStateCreateInfo pipeline_create_rasterization_info();

VkPipelineMultisampleStateCreateInfo pipeline_create_multisample_info();

VkPipelineDepthStencilStateCreateInfo pipeline_create_depth_stencil_info();

VkPipelineColorBlendStateCreateInfo pipeline_create_color_blend_info();

void pipeline_create(const LogicalDevice& device, const Swapchain& swapchain);

void pipeline_destroy(const LogicalDevice& device);
