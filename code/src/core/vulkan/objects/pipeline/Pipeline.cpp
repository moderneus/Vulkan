#include "core/vulkan/objects/pipeline/Pipeline.hpp"
#include "core/vulkan/objects/pipeline/PipelineLayout.hpp"
#include "core/vulkan/objects/pipeline/ShaderModule.hpp"
#include "core/vulkan/objects/swapchain/Swapchain.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "core/vulkan/objects/renderpass/RenderPass.hpp"
#include "core/vulkan/objects/buffers/types/Vertex.hpp"
#include "util/debug/Logger.hpp"

VkViewport pl_create_viewport(const swapchain_state_t &st) 
{
	VkViewport vp = {};
	vp.x = 0.0f;
	vp.y = 0.0f;
	vp.width = static_cast<float>(st.extent.width);
	vp.height = static_cast<float>(st.extent.height);
	vp.minDepth = 0.0f;
	vp.maxDepth = 1.0f;
	return vp;
}

VkRect2D pl_create_scissor(const swapchain_state_t &st) 
{
	VkRect2D sc = {};
	sc.offset = {0, 0};
	sc.extent = st.extent;
	return sc;
}

VkPipelineColorBlendAttachmentState pl_create_col_blend_att() 
{
	log_info("Creating a Color Blend Attachment...");

	VkPipelineColorBlendAttachmentState att = {};

	att.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | 
				    VK_COLOR_COMPONENT_G_BIT | 
				    VK_COLOR_COMPONENT_B_BIT | 
				    VK_COLOR_COMPONENT_A_BIT;

	att.blendEnable = VK_FALSE;
	att.alphaBlendOp = VK_BLEND_OP_ADD;
	
	log_info("The Color Blend Attachment was Created.");

	return att;
}

std::vector<shader_ref_t> pl_create_shdr_refs(const std::array<shader_t, 2> &shdrs)
{
	log_info("Creating the Shader Modules References...");

	std::vector<shader_ref_t> refs;
	refs.push_back({shdrs[0].handle, VK_SHADER_STAGE_VERTEX_BIT});
	refs.push_back({shdrs[1].handle, VK_SHADER_STAGE_FRAGMENT_BIT});

	log_info("The Shader Module References were Created.");

	return refs;
}

VkPipelineShaderStageCreateInfo pl_create_shdr_stage_info(const shader_ref_t &ref) 
{
	log_info("Creating the Shader Stage Info...");

	VkPipelineShaderStageCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	info.stage = ref.stage;
	info.module = ref.handle;
	info.pName = "main";

	log_info("The Shader Stage Info was Created.");

	return info;
}

std::vector<VkPipelineShaderStageCreateInfo> pl_create_shdr_stage_infos(const pipeline_cfg_t &cfg)
{
	log_info("Creating the Shader Stage Infos...");

	std::vector<VkPipelineShaderStageCreateInfo> infos;
	for(const auto& ref : cfg.shdr_refs) {
		infos.push_back(pl_create_shdr_stage_info(ref));
	}

	log_info("The Shader Stage Infos were Created!");

	return infos;
}

VkPipelineDynamicStateCreateInfo pl_create_dyn_state_info(const pipeline_cfg_t &cfg) 
{
	log_info("Creating a Dynamic State Info...");

	VkPipelineDynamicStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	info.dynamicStateCount = static_cast<uint32_t>(cfg.dyn_st.size());
	info.pDynamicStates = cfg.dyn_st.data();

	log_info("The Dynamic State Info was Created.");

	return info;
}

VkPipelineVertexInputStateCreateInfo pl_create_vert_input_info(const pipeline_cfg_t &cfg) 
{
	log_info("Creating a Vertex Input Info...");

	VkPipelineVertexInputStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	info.vertexBindingDescriptionCount = 1;
	info.pVertexBindingDescriptions = &cfg.bind_desc;
	info.vertexAttributeDescriptionCount = static_cast<uint32_t>(cfg.attrib_desc.size());
	info.pVertexAttributeDescriptions = cfg.attrib_desc.data();

	log_info("The Vertex Input Info was Created.");

	return info;
}

VkPipelineInputAssemblyStateCreateInfo pl_create_input_asm_info() 
{
	log_info("Creating a Input Assembly Info...");

	VkPipelineInputAssemblyStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	info.primitiveRestartEnable = VK_FALSE;

	log_info("The Input Assembly Info was Created.");

	return info;
}

VkPipelineViewportStateCreateInfo pl_create_vp_info(const pipeline_cfg_t &cfg) 
{
	log_info("Creating the Viewport Info...");

	VkPipelineViewportStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	info.viewportCount = 1;
	info.pViewports = &cfg.vp;
	info.scissorCount = 1;
	info.pScissors = &cfg.sci;

	log_info("The Viewport Info was Created.");

	return info;
}

VkPipelineRasterizationStateCreateInfo pl_create_rast_info() 
{
	log_info("Creating a Rasterization Info...");

	VkPipelineRasterizationStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	info.depthClampEnable = VK_FALSE;
	info.rasterizerDiscardEnable = VK_FALSE;
	info.polygonMode = VK_POLYGON_MODE_FILL;
	info.lineWidth = 1.0f;
	info.cullMode = VK_CULL_MODE_BACK_BIT;
	info.frontFace = VK_FRONT_FACE_CLOCKWISE;
	info.depthBiasEnable = VK_FALSE;
	info.depthBiasConstantFactor = 0.0f;
	info.depthBiasClamp = 0.0f;
	info.depthBiasSlopeFactor = 0.0f;

	log_info("The Rasterization Info was Created.");

	return info;
}

VkPipelineMultisampleStateCreateInfo pl_create_msaa_info() 
{
	log_info("Creating a Multisampling Info...");

	VkPipelineMultisampleStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	info.sampleShadingEnable = VK_FALSE;
	info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	log_info("The Multisampling Info was Created.");

	return info;
}

#if 0
VkPipelineDepthStencilStateCreateInfo pipeline_create_depth_stencil_info() {
    
}
#endif

VkPipelineColorBlendStateCreateInfo pl_create_col_blend_info(const pipeline_cfg_t &cfg) 
{
	log_info("Creating the Color Blend Info...");

	VkPipelineColorBlendStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	info.logicOpEnable = VK_FALSE;
	info.attachmentCount = 1;
	info.pAttachments = &cfg.att;

	log_info("The Color Blend Info was Created.");

	return info;
}

VkGraphicsPipelineCreateInfo pl_create_info(const pipeline_info_t &pl_info, const layout_t &layout, const render_pass_t &rp)
{
	log_info("Creating the Pipeline Info...");

	VkGraphicsPipelineCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	info.stageCount = 2;
	info.pStages = pl_info.shdr_stages.data();
	info.pVertexInputState = &pl_info.vert_input;
	info.pInputAssemblyState = &pl_info.asm_input;
	info.pViewportState = &pl_info.vp;
	info.pRasterizationState = &pl_info.rast;
	info.pMultisampleState = &pl_info.msaa;
	info.pDepthStencilState = nullptr;
	info.pColorBlendState = &pl_info.col_blend;
	info.pDynamicState = &pl_info.dyn_st;
	info.layout = layout.handle;
	info.renderPass = rp.handle;
	info.subpass = 0;

	log_info("The Pipeline Info was Created.");

	return info;
}

void pl_create(pipeline_t *pl, const device_t &dev, const layout_t &layout, const render_pass_t &rp, const swapchain_state_t &st, const std::array<shader_t, 2> &shdrs)
{
	log_info("Creating a Pipeline...");

	pipeline_cfg_t cfg = {};
	cfg.shdr_refs= pl_create_shdr_refs(shdrs);
	cfg.vp = pl_create_viewport(st);
	cfg.sci = pl_create_scissor(st);
	cfg.att = pl_create_col_blend_att();
	cfg.bind_desc= vert_get_bind_desc();
	cfg.attrib_desc= vert_get_attrib_desc();

	pipeline_info_t info = {};
	info.shdr_stages = pl_create_shdr_stage_infos(cfg);
	info.vert_input = pl_create_vert_input_info(cfg);
	info.asm_input = pl_create_input_asm_info();
	info.vp = pl_create_vp_info(cfg);
	info.rast = pl_create_rast_info();
	info.msaa = pl_create_msaa_info();
	info.col_blend = pl_create_col_blend_info(cfg);
	info.dyn_st = pl_create_dyn_state_info(cfg);

	VkGraphicsPipelineCreateInfo pl_info = pl_create_info(info, layout, rp);

	if (vkCreateGraphicsPipelines(dev.handle, VK_NULL_HANDLE, 1, &pl_info, nullptr, &pl->handle) != VK_SUCCESS) {
		log_critical("Failed to Create the Graphics Pipeline.");
	}

	log_info("The Pipeline was Created.");
}

void pl_destroy(const pipeline_t &pl, const device_t &dev) 
{
	log_info("Destroying the Pipeline...");

	if (pl.handle == VK_NULL_HANDLE) {
		log_error("Cannot Destroy the Pipeline::Pipeline is not Created.");
	}

	vkDestroyPipeline(dev.handle, pl.handle, nullptr);

	log_info("The Pipeline was Destroyed.");
}
