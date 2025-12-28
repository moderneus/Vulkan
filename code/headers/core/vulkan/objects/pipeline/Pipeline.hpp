#pragma once

#include "core/vulkan/objects/pipeline/ShaderModule.hpp"

#include <vulkan/vulkan.h>

#include <array>

struct LogicalDevice;
struct Swapchain;
struct PipelineLayout;
struct RenderPass;

struct Pipeline {
    VkPipeline handle = VK_NULL_HANDLE;
    ShaderModule vert_shader;
    ShaderModule frag_shader;
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

VkPipelineColorBlendAttachmentState pipeline_create_color_blend_attachment();

VkPipelineDepthStencilStateCreateInfo pipeline_create_depth_stencil_info();

void pipeline_create_shader_modules(Pipeline* pipeline, const LogicalDevice& device);

std::array<VkPipelineShaderStageCreateInfo, 2> pipeline_create_shader_stage_info();

VkPipelineDynamicStateCreateInfo pipeline_create_dynamic_state_info();

VkPipelineVertexInputStateCreateInfo pipeline_create_vertex_input_info();

VkPipelineInputAssemblyStateCreateInfo pipeline_create_input_assembly_info();

VkPipelineViewportStateCreateInfo pipeline_create_viewport_info(const VkViewport& viewport, const VkRect2D& scissor);

VkPipelineRasterizationStateCreateInfo pipeline_create_rasterization_info();

VkPipelineMultisampleStateCreateInfo pipeline_create_multisample_info();

VkPipelineColorBlendStateCreateInfo pipeline_create_color_blend_info(const VkPipelineColorBlendAttachmentState* attachment);

VkGraphicsPipelineCreateInfo pipeline_create_info(const PipelineState& state, const PipelineLayout& layout, const RenderPass& render_pass);

void pipeline_create(Pipeline* pipeline, const LogicalDevice& device, const Swapchain& swapchain, const PipelineLayout& layout, const RenderPass& render_pass);

void pipeline_destroy(const Pipeline& pipeline, const LogicalDevice& device);
