#ifndef MOD_PIPELINE_HPP
#define MOD_PIPELINE_HPP

#include "core/vulkan/obj/pipeline/shader.hpp"

#include <vulkan/vulkan.h>

#include <vector>
#include <array>

struct swapchain_state;
struct pipeline_layout;
struct render_pass;
struct device;

struct pipeline {
	VkPipeline handle = VK_NULL_HANDLE;
};

struct pipeline_info {
	std::vector<VkPipelineShaderStageCreateInfo>		shdr_stages = {};
	VkPipelineDynamicStateCreateInfo			dyn_state   = {};
	VkPipelineVertexInputStateCreateInfo			vert_input  = {};
	VkPipelineInputAssemblyStateCreateInfo			asm_input   = {};
	VkPipelineViewportStateCreateInfo			vp	    = {};
	VkPipelineRasterizationStateCreateInfo			rast	    = {};
	VkPipelineMultisampleStateCreateInfo			msaa	    = {};
	VkPipelineDepthStencilStateCreateInfo			ds	    = {};
	VkPipelineColorBlendStateCreateInfo			col_blend   = {};
};

struct pipeline_config {
	std::vector<shader_reference>				shdr_refs   = {};
	VkViewport						vp	    = {};
	VkRect2D						scissor	    = {};
	VkPipelineColorBlendAttachmentState			att	    = {};
	std::vector<VkDynamicState>				dyn_state   = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
	VkVertexInputBindingDescription				bind_desc   = {};
	std::array<VkVertexInputAttributeDescription, 3>	attrib_desc = {};
};

VkViewport pipeline_create_viewport(const swapchain_state &st);

VkRect2D pipeline_create_scissor(const swapchain_state &st);

VkPipelineColorBlendAttachmentState pipeline_create_col_blend_att();

VkPipelineDepthStencilStateCreateInfo pipeline_create_ds_info();

std::vector<shader_reference> pipeline_create_shdr_refs(const std::array<shader, 2> &shdrs);

VkPipelineShaderStageCreateInfo pipeline_create_shdr_stage_info(const shader_reference &ref);

std::vector<VkPipelineShaderStageCreateInfo> pipeline_create_shdr_stage_infos(const pipeline_config &cfg);

VkPipelineDynamicStateCreateInfo pipeline_create_dyn_state_info();

VkPipelineVertexInputStateCreateInfo pipeline_create_vert_input_info(const pipeline_config &cfg);

VkPipelineInputAssemblyStateCreateInfo pipeline_create_asm_input_info();

VkPipelineViewportStateCreateInfo pipeline_create_viewport_info(const pipeline_config &cfg);

VkPipelineRasterizationStateCreateInfo pipeline_create_rast_info();

VkPipelineMultisampleStateCreateInfo pipeline_create_msaa_info();

VkPipelineColorBlendStateCreateInfo pipeline_create_col_blend_info(const pipeline_config &cfg);

VkGraphicsPipelineCreateInfo pipeline_create_info(const pipeline_info &pl_info, const pipeline_layout &lyt, const render_pass &rp);

void pipeline_create(pipeline *pl, const device &dev, const pipeline_layout &lyt, const render_pass &rp, 
		     const swapchain_state &st, const std::array<shader, 2> &shdrs);

void pipeline_destroy(const pipeline &pl, const device &dev);

#endif
