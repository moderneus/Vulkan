#ifndef MOD_PIPELINE_HPP
#define MOD_PIPELINE_HPP

#include "core/vulkan/objects/pipeline/ShaderModule.hpp"

#include <vulkan/vulkan.h>

#include <array>

struct device_t;
struct swapchain_t;
struct pipeline_layout_t;
struct render_pass_t;

struct pipeline_t
{
	VkPipeline		handle = VK_NULL_HANDLE;
	shader_module_t		vert_shader;
	shader_module_t		frag_shader;
};

struct pipeline_state_t
{
	std::array<VkPipelineShaderStageCreateInfo, 2>		shader_stages	    = {};
	VkPipelineDynamicStateCreateInfo			dynamic_state_info  = {};
	VkPipelineVertexInputStateCreateInfo			vertex_input_info   = {};
	VkPipelineInputAssemblyStateCreateInfo			input_assembly_info = {};
	VkPipelineViewportStateCreateInfo			viewport_info       = {};
	VkPipelineRasterizationStateCreateInfo			rasterization_info  = {};
	VkPipelineMultisampleStateCreateInfo			multisample_info    = {};
	VkPipelineDepthStencilStateCreateInfo			depth_stencil_info  = {};
	VkPipelineColorBlendStateCreateInfo			color_blend_info    = {};
};

VkViewport pipeline_create_viewport(const swapchain_t& swapchain);

VkRect2D pipeline_create_scissor(const swapchain_t& swapchain);

VkPipelineColorBlendAttachmentState pipeline_create_color_blend_attachment();

VkPipelineDepthStencilStateCreateInfo pipeline_create_depth_stencil_info();

void pipeline_create_shader_modules(pipeline_t* pipeline, const device_t& device);

std::array<VkPipelineShaderStageCreateInfo, 2> pipeline_create_shader_stage_info();

VkPipelineDynamicStateCreateInfo pipeline_create_dynamic_state_info();

VkPipelineVertexInputStateCreateInfo pipeline_create_vertex_input_info();

VkPipelineInputAssemblyStateCreateInfo pipeline_create_input_assembly_info();

VkPipelineViewportStateCreateInfo pipeline_create_viewport_info(const VkViewport& viewport, const VkRect2D& scissor);

VkPipelineRasterizationStateCreateInfo pipeline_create_rasterization_info();

VkPipelineMultisampleStateCreateInfo pipeline_create_multisample_info();

VkPipelineColorBlendStateCreateInfo pipeline_create_color_blend_info(const VkPipelineColorBlendAttachmentState* attachment);

VkGraphicsPipelineCreateInfo pipeline_create_info(const pipeline_state_t& state, const pipeline_layout_t& layout, const render_pass_t& render_pass);

void pipeline_create(pipeline_t* pipeline, const device_t& device, const swapchain_t& swapchain, const pipeline_layout_t& layout, const render_pass_t& render_pass);

void pipeline_destroy(const pipeline_t& pipeline, const device_t& device);

#endif
