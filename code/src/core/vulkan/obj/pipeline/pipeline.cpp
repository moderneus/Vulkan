#include "core/vulkan/obj/pipeline/pipeline.hpp"
#include "core/vulkan/obj/pipeline/layout.hpp"
#include "core/vulkan/obj/pipeline/shader.hpp"
#include "core/vulkan/obj/swapchain/swapchain.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "core/vulkan/obj/renderpass/render_pass.hpp"
#include "core/vulkan/obj/buffer/vertex.hpp"
#include "util/debug/log.hpp"

VkViewport pipeline_create_viewport(const swapchain_state &st) 
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

VkRect2D pipeline_create_scissor(const swapchain_state &st) 
{
	VkRect2D scissor = {};
	scissor.offset = {0, 0};
	scissor.extent = st.extent;
	return scissor;
}

VkPipelineColorBlendAttachmentState pipeline_create_col_blend_att() 
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

std::vector<shader_reference> pipeline_create_shdr_refs(const std::array<shader, 2> &shdrs)
{
	log_info("Creating the Shader Modules References...");

	std::vector<shader_reference> refs;
	refs.push_back({shdrs[0].handle, VK_SHADER_STAGE_VERTEX_BIT});
	refs.push_back({shdrs[1].handle, VK_SHADER_STAGE_FRAGMENT_BIT});

	log_info("The Shader Module References were Created.");

	return refs;
}

VkPipelineShaderStageCreateInfo pipeline_create_shdr_stage_info(const shader_reference &ref) 
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

std::vector<VkPipelineShaderStageCreateInfo> pipeline_create_shdr_stage_infos(const pipeline_config &cfg)
{
	log_info("Creating the Shader Stage Infos...");

	std::vector<VkPipelineShaderStageCreateInfo> infos;

	for(const auto& ref : cfg.shdr_refs)
		infos.push_back(pipeline_create_shdr_stage_info(ref));

	log_info("The Shader Stage Infos were Created!");

	return infos;
}

VkPipelineDynamicStateCreateInfo pipeline_create_dyn_state_info(const pipeline_config &cfg) 
{
	log_info("Creating a Dynamic State Info...");

	VkPipelineDynamicStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	info.dynamicStateCount = static_cast<uint32_t>(cfg.dyn_state.size());
	info.pDynamicStates = cfg.dyn_state.data();

	log_info("The Dynamic State Info was Created.");

	return info;
}

VkPipelineVertexInputStateCreateInfo pipeline_create_vert_input_info(const pipeline_config &cfg) 
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

VkPipelineInputAssemblyStateCreateInfo pipeline_create_asm_input_info() 
{
	log_info("Creating a Input Assembly Info...");

	VkPipelineInputAssemblyStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	info.primitiveRestartEnable = VK_FALSE;

	log_info("The Input Assembly Info was Created.");

	return info;
}

VkPipelineViewportStateCreateInfo pipeline_create_viewport_info(const pipeline_config &cfg) 
{
	log_info("Creating the Viewport Info...");

	VkPipelineViewportStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	info.viewportCount = 1;
	info.pViewports = &cfg.vp;
	info.scissorCount = 1;
	info.pScissors = &cfg.scissor;

	log_info("The Viewport Info was Created.");

	return info;
}

VkPipelineRasterizationStateCreateInfo pipeline_create_rast_info() 
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

VkPipelineMultisampleStateCreateInfo pipeline_create_msaa_info() 
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

VkPipelineColorBlendStateCreateInfo pipeline_create_col_blend_info(const pipeline_config &cfg) 
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

VkGraphicsPipelineCreateInfo pipeline_create_info(const pipeline_info &pl_info, const layout &lyt, const render_pass &rp)
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
	info.pDynamicState = &pl_info.dyn_state;
	info.layout = lyt.handle;
	info.renderPass = rp.handle;
	info.subpass = 0;

	log_info("The Pipeline Info was Created.");

	return info;
}

void pipeline_create(pipeline *pl, const device &dev, const layout &lyt, const render_pass &rp, const swapchain_state &st, const std::array<shader, 2> &shdrs)
{
	log_info("Creating a Pipeline...");

	pipeline_config cfg = {};
	cfg.shdr_refs = pipeline_create_shdr_refs(shdrs);
	cfg.vp = pipeline_create_viewport(st);
	cfg.scissor = pipeline_create_scissor(st);
	cfg.att = pipeline_create_col_blend_att();
	cfg.bind_desc = vertex_get_bind_desc();
	cfg.attrib_desc= vertex_get_attrib_desc();

	pipeline_info pl_info = {};
	pl_info.shdr_stages = pipeline_create_shdr_stage_infos(cfg);
	pl_info.vert_input = pipeline_create_vert_input_info(cfg);
	pl_info.asm_input = pipeline_create_asm_input_info();
	pl_info.vp = pipeline_create_viewport_info(cfg);
	pl_info.rast = pipeline_create_rast_info();
	pl_info.msaa = pipeline_create_msaa_info();
	pl_info.col_blend = pipeline_create_col_blend_info(cfg);
	pl_info.dyn_state = pipeline_create_dyn_state_info(cfg);

	VkGraphicsPipelineCreateInfo info = pipeline_create_info(pl_info, lyt, rp);

	if (vkCreateGraphicsPipelines(dev.handle, VK_NULL_HANDLE, 1, &info, nullptr, &pl->handle) != VK_SUCCESS)
		log_critical("Failed to Create the Graphics Pipeline.");

	log_info("The Pipeline was Created.");
}

void pipeline_destroy(const pipeline &pl, const device &dev) 
{
	log_info("Destroying the Pipeline...");

	if (pl.handle == VK_NULL_HANDLE)
		log_error("Cannot Destroy the Pipeline::Pipeline is not Created.");

	vkDestroyPipeline(dev.handle, pl.handle, nullptr);

	log_info("The Pipeline was Destroyed.");
}
