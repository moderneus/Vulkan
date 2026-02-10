#ifndef MOD_PIPELINE_HPP
#define MOD_PIPELINE_HPP

#include "core/vulkan/objects/pipeline/ShaderModule.hpp"

#include <vulkan/vulkan.h>

#include <vector>
#include <array>

struct swapchain_state_t;
struct pipeline_layout_t;
struct render_pass_t;
struct device_t;

struct pipeline_t
{
	VkPipeline handle = VK_NULL_HANDLE;
};

struct pipeline_info_t
{
	std::vector<VkPipelineShaderStageCreateInfo>			shader_stages  = {};
	VkPipelineDynamicStateCreateInfo				dynamic_state  = {};
	VkPipelineVertexInputStateCreateInfo				vert_input     = {};
	VkPipelineInputAssemblyStateCreateInfo				input_asm      = {};
	VkPipelineViewportStateCreateInfo				viewport       = {};
	VkPipelineRasterizationStateCreateInfo				rasterization  = {};
	VkPipelineMultisampleStateCreateInfo				multisample    = {};
	VkPipelineDepthStencilStateCreateInfo				depth_stencil  = {};
	VkPipelineColorBlendStateCreateInfo				col_blend      = {};
};

struct pipeline_config_t
{
	std::vector<shader_ref_t>					shader_refs         = {};
	VkViewport							viewport	    = {};
	VkRect2D							scissor             = {};
	VkPipelineColorBlendAttachmentState				att		    = {};
	std::vector<VkDynamicState>					dyn_st	            = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
	VkVertexInputBindingDescription					bind_desc           = {};
	std::array<VkVertexInputAttributeDescription, 2>		attrib_desc         = {};
};

VkViewport pipeline_create_viewport(const swapchain_state_t &st);

VkRect2D pipeline_create_scissor(const swapchain_state_t &st);

VkPipelineColorBlendAttachmentState pipeline_create_col_blend_att();

VkPipelineDepthStencilStateCreateInfo pipeline_create_depth_stencil_info();

std::vector<shader_module_ref_t> pipeline_create_shader_module_refs(const std::array<shader_t, 2> &shaders);

VkPipelineShaderStageCreateInfo pipeline_create_shader_stage_info(const shader_ref_t &ref);

std::vector<VkPipelineShaderStageCreateInfo> pipeline_create_shader_stage_infos(const pipeline_config_t &cfg);

VkPipelineDynamicStateCreateInfo pipeline_create_dynamic_state_info();

VkPipelineVertexInputStateCreateInfo pipeline_create_vert_input_info(const pipeline_config_t &cfg);

VkPipelineInputAssemblyStateCreateInfo pipeline_create_input_asm_info();

VkPipelineViewportStateCreateInfo pipeline_create_viewport_info(const pipeline_config_t &cfg);

VkPipelineRasterizationStateCreateInfo pipeline_create_rasterization_info();

VkPipelineMultisampleStateCreateInfo pipeline_create_multisample_info();

VkPipelineColorBlendStateCreateInfo pipeline_create_col_blend_info(const pipeline_config_t &cfg);

VkGraphicsPipelineCreateInfo pipeline_create_info(const pipeline_info_t &pipe_info, const pipeline_layout_t &layout, const render_pass_t &rp);

void pipeline_create(pipeline_t *pipeline, const device_t &dev, const pipeline_layout_t &layout, const render_pass_t &rp, const swapchain_state_t &st, const std::array<shader_t, 2> &shaders);

void pipeline_destroy(const pipeline_t &pipeline, const device_t &dev);

#endif
