#ifndef MOD_PIPELINE_HPP
#define MOD_PIPELINE_HPP

#include "core/vulkan/objects/pipeline/ShaderModule.hpp"

#include <vulkan/vulkan.h>

#include <vector>
#include <array>

struct swapchain_state_t;
struct layout_t;
struct render_pass_t;
struct device_t;

struct pipeline_t
{
	VkPipeline handle = VK_NULL_HANDLE;
};

struct pipeline_info_t
{
	std::vector<VkPipelineShaderStageCreateInfo>			shdr_stages    = {};
	VkPipelineDynamicStateCreateInfo				dyn_st	       = {};
	VkPipelineVertexInputStateCreateInfo				vert_input     = {};
	VkPipelineInputAssemblyStateCreateInfo				asm_input      = {};
	VkPipelineViewportStateCreateInfo				vp	       = {};
	VkPipelineRasterizationStateCreateInfo				rast	       = {};
	VkPipelineMultisampleStateCreateInfo				msaa	       = {};
	VkPipelineDepthStencilStateCreateInfo				ds	       = {};
	VkPipelineColorBlendStateCreateInfo				col_blend      = {};
};

struct pipeline_cfg_t
{
	std::vector<shader_ref_t>					shdr_refs           = {};
	VkViewport							vp		    = {};
	VkRect2D							sci		    = {};
	VkPipelineColorBlendAttachmentState				att		    = {};
	std::vector<VkDynamicState>					dyn_st	            = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
	VkVertexInputBindingDescription					bind_desc           = {};
	std::array<VkVertexInputAttributeDescription, 2>		attrib_desc         = {};
};

VkViewport pl_create_vp(const swapchain_state_t &st);

VkRect2D pl_create_sci(const swapchain_state_t &st);

VkPipelineColorBlendAttachmentState pl_create_col_blend_att();

VkPipelineDepthStencilStateCreateInfo pl_create_ds_info();

std::vector<shader_ref_t> pl_create_shdr_refs(const std::array<shader_t, 2> &shdrs);

VkPipelineShaderStageCreateInfo pl_create_shdr_stage_info(const shader_ref_t &ref);

std::vector<VkPipelineShaderStageCreateInfo> pl_create_shdr_stage_infos(const pipeline_cfg_t &cfg);

VkPipelineDynamicStateCreateInfo pl_create_dyn_st_info();

VkPipelineVertexInputStateCreateInfo pl_create_vert_input_info(const pipeline_cfg_t &cfg);

VkPipelineInputAssemblyStateCreateInfo pl_create_asm_input_info();

VkPipelineViewportStateCreateInfo pl_create_vp_info(const pipeline_cfg_t &cfg);

VkPipelineRasterizationStateCreateInfo pl_create_rast_info();

VkPipelineMultisampleStateCreateInfo pl_create_msaa_info();

VkPipelineColorBlendStateCreateInfo pl_create_col_blend_info(const pipeline_cfg_t &cfg);

VkGraphicsPipelineCreateInfo pl_create_info(const pipeline_info_t &pl_info, const layout_t &layout, const render_pass_t &rp);

void pl_create(pipeline_t *pl, const device_t &dev, const layout_t &layout, const render_pass_t &rp, const swapchain_state_t &st, const std::array<shader_t, 2> &shdrs);

void pl_destroy(const pipeline_t &pipeline, const device_t &dev);

#endif
