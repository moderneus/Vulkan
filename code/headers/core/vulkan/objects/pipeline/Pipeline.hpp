#ifndef MOD_PIPELINE_HPP
#define MOD_PIPELINE_HPP

#include "core/vulkan/objects/pipeline/ShaderModule.hpp"

#include <vulkan/vulkan.h>

#include <vector>
#include <array>

struct swapchain_config_t;
struct pipeline_layout_t;
struct render_pass_t;
struct device_t;

struct pipeline_t
{
	VkPipeline handle = VK_NULL_HANDLE;
};

struct pipeline_state_t
{
	std::vector<VkPipelineShaderStageCreateInfo>		shader_stages	    = {};
	VkPipelineDynamicStateCreateInfo			dynamic_state_info  = {};
	VkPipelineVertexInputStateCreateInfo			vertex_input_info   = {};
	VkPipelineInputAssemblyStateCreateInfo			input_assembly_info = {};
	VkPipelineViewportStateCreateInfo			viewport_info       = {};
	VkPipelineRasterizationStateCreateInfo			rasterization_info  = {};
	VkPipelineMultisampleStateCreateInfo			multisample_info    = {};
	VkPipelineDepthStencilStateCreateInfo			depth_stencil_info  = {};
	VkPipelineColorBlendStateCreateInfo			color_blend_info    = {};
};

struct pipeline_config_t
{
	pipeline_state_t				state		   = {};
	std::vector<shader_module_ref_t>		shader_module_refs = {};
	VkViewport					viewport	   = {};
	VkRect2D					scissor            = {};
	VkPipelineColorBlendAttachmentState		attachment         = {};
	std::vector<VkDynamicState>			dynamic_states     = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
};

VkViewport pipeline_create_viewport(const swapchain_config_t& cfg);

VkRect2D pipeline_create_scissor(const swapchain_config_t& cfg);

VkPipelineColorBlendAttachmentState pipeline_create_color_blend_attachment();

VkPipelineDepthStencilStateCreateInfo pipeline_create_depth_stencil_info();

std::vector<shader_module_ref_t> pipeline_create_shader_module_refs(const std::array<shader_module_t, 2>& shader_modules);

VkPipelineShaderStageCreateInfo pipeline_create_shader_stage_info(const shader_module_ref_t& shader_module);

std::vector<VkPipelineShaderStageCreateInfo> pipeline_create_shader_stage_infos(const std::vector<shader_module_ref_t>& shader_modules);

VkPipelineDynamicStateCreateInfo pipeline_create_dynamic_state_info();

VkPipelineVertexInputStateCreateInfo pipeline_create_vertex_input_info();

VkPipelineInputAssemblyStateCreateInfo pipeline_create_input_assembly_info();

VkPipelineViewportStateCreateInfo pipeline_create_viewport_info(const VkViewport& viewport, const VkRect2D& scissor);

VkPipelineRasterizationStateCreateInfo pipeline_create_rasterization_info();

VkPipelineMultisampleStateCreateInfo pipeline_create_multisample_info();

VkPipelineColorBlendStateCreateInfo pipeline_create_color_blend_info(const VkPipelineColorBlendAttachmentState* attachment);

VkGraphicsPipelineCreateInfo pipeline_create_info(const pipeline_state_t& state, const pipeline_layout_t& layout, const render_pass_t& render_pass);

void pipeline_config_setup(pipeline_config_t* pipeline_cfg, const swapchain_config_t& swapchain_cfg, const std::array<shader_module_t, 2>& shader_modules);

void pipeline_create(pipeline_t* pipeline, const device_t& device, const pipeline_config_t& cfg, const pipeline_layout_t& pipeline_layout, const render_pass_t& render_pass);

void pipeline_destroy(const pipeline_t& pipeline, const device_t& device);

#endif
