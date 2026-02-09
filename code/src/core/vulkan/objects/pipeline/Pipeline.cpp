#include "core/vulkan/objects/pipeline/Pipeline.hpp"
#include "core/vulkan/objects/pipeline/PipelineLayout.hpp"
#include "core/vulkan/objects/pipeline/ShaderModule.hpp"
#include "core/vulkan/objects/swapchain/Swapchain.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "core/vulkan/objects/renderpass/RenderPass.hpp"
#include "core/vulkan/objects/buffers/types/Vertex.hpp"
#include "util/debug/Logger.hpp"

VkViewport pipeline_create_viewport(const swapchain_state_t &st) 
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

VkRect2D pipeline_create_scissor(const swapchain_state_t &st) 
{
	VkRect2D sc = {};
	sc.offset = {0, 0};
	sc.extent = st.extent;
	return sc;
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

std::vector<shader_module_ref_t> pipeline_create_shader_module_refs(const std::array<shader_module_t, 2> &shaders)
{
	log_info("Creating the Shader Modules References...");

	std::vector<shader_module_ref_t> refs;
	refs.push_back({shaders[0].handle, VK_SHADER_STAGE_VERTEX_BIT});
	refs.push_back({shaders[1].handle, VK_SHADER_STAGE_FRAGMENT_BIT});

	log_info("The Shader Module References were Created.");

	return refs;
}

VkPipelineShaderStageCreateInfo pipeline_create_shader_stage_info(const shader_module_ref_t &ref) 
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

std::vector<VkPipelineShaderStageCreateInfo> pipeline_create_shader_stage_infos(const pipeline_config_t &cfg)
{
	log_info("Creating the Shader Stage Infos...");

	std::vector<VkPipelineShaderStageCreateInfo> infos;
	for(const auto& ref : cfg.shader_refs) {
		infos.push_back(pipeline_create_shader_stage_info(ref));
	}

	log_info("The Shader Stage Infos were Created!");

	return infos;
}

VkPipelineDynamicStateCreateInfo pipeline_create_dynamic_state_info(const pipeline_config_t &cfg) 
{
	log_info("Creating a Dynamic State Info...");

	VkPipelineDynamicStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	info.dynamicStateCount = static_cast<uint32_t>(cfg.dynamic_states.size());
	info.pDynamicStates = cfg.dynamic_states.data();

	log_info("The Dynamic State Info was Created.");

	return info;
}

VkPipelineVertexInputStateCreateInfo pipeline_create_vert_input_info(const pipeline_config_t &cfg) 
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

VkPipelineInputAssemblyStateCreateInfo pipeline_create_input_asm_info() 
{
	log_info("Creating a Input Assembly Info...");

	VkPipelineInputAssemblyStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	info.primitiveRestartEnable = VK_FALSE;

	log_info("The Input Assembly Info was Created.");

	return info;
}

VkPipelineViewportStateCreateInfo pipeline_create_viewport_info(const pipeline_config_t &cfg) 
{
	log_info("Creating the Viewport Info...");

	VkPipelineViewportStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	info.viewportCount = 1;
	info.pViewports = &cfg.viewport;
	info.scissorCount = 1;
	info.pScissors = &cfg.scissor;

	log_info("The Viewport Info was Created.");

	return info;
}

VkPipelineRasterizationStateCreateInfo pipeline_create_rasterization_info() 
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

VkPipelineMultisampleStateCreateInfo pipeline_create_multisample_info() 
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

VkPipelineColorBlendStateCreateInfo pipeline_create_col_blend_info(const pipeline_config_t &cfg) 
{
	log_info("Creating the Color Blend Info...");

	VkPipelineColorBlendStateCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	info.logicOpEnable = VK_FALSE;
	info.attachmentCount = 1;
	info.pAttachments = &cfg.attachment;

	log_info("The Color Blend Info was Created.");

	return info;
}

VkGraphicsPipelineCreateInfo pipeline_create_info(const pipeline_info_t &pipe_info, const pipeline_layout_t &layout, const render_pass_t &render_pass)
{
	log_info("Creating the Pipeline Info...");

	VkGraphicsPipelineCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	info.stageCount = 2;
	info.pStages = pipe_info.shader_stages.data();
	info.pVertexInputState = &pipe_info.vert_input;
	info.pInputAssemblyState = &pipe_info.input_asm;
	info.pViewportState = &pipe_info.viewport;
	info.pRasterizationState = &pipe_info.rasterization;
	info.pMultisampleState = &pipe_info.multisample;
	info.pDepthStencilState = nullptr;
	info.pColorBlendState = &pipe_info.col_blend;
	info.pDynamicState = &pipe_info.dynamic_state;
	info.layout = layout.handle;
	info.renderPass = render_pass.handle;
	info.subpass = 0;

	log_info("The Pipeline Info was Created.");

	return info;
}

void pipeline_create(pipeline_t *pipeline, const device_t &dev, const pipeline_layout_t &layout, const render_pass_t &rp, const swapchain_state_t &st, const std::array<shader_module_t, 2> &shaders) 
{
	log_info("Creating a Pipeline...");

	pipeline_config_t cfg = {};
	cfg.shader_refs= pipeline_create_shader_module_refs(shaders);
	cfg.viewport = pipeline_create_viewport(st);
	cfg.scissor = pipeline_create_scissor(st);
	cfg.attachment = pipeline_create_col_blend_att();
	cfg.bind_desc= vertex_get_binding_description();
	cfg.attrib_desc= vertex_get_attrib_description();

	pipeline_info_t info = {};
	info.shader_stages= pipeline_create_shader_stage_infos(cfg);
	info.vert_input = pipeline_create_vert_input_info(cfg);
	info.input_asm  = pipeline_create_input_asm_info();
	info.viewport = pipeline_create_viewport_info(cfg);
	info.rasterization = pipeline_create_rasterization_info();
	info.multisample = pipeline_create_multisample_info();
	info.col_blend = pipeline_create_col_blend_info(cfg);
	info.dynamic_state = pipeline_create_dynamic_state_info(cfg);

	VkGraphicsPipelineCreateInfo pipe_info = pipeline_create_info(info, layout, rp);

	if (vkCreateGraphicsPipelines(dev.handle, VK_NULL_HANDLE, 1, &pipe_info, nullptr, &pipeline->handle) != VK_SUCCESS) {
		log_critical("Failed to Create the Graphics Pipeline.");
	}

	log_info("The Pipeline was Created.");
}

void pipeline_destroy(const pipeline_t &pipeline, const device_t &dev) 
{
	log_info("Destroying the Pipeline...");

	if (pipeline.handle == VK_NULL_HANDLE) {
		log_error("Cannot Destroy the Pipeline::Pipeline is not Created.");
	}

	vkDestroyPipeline(dev.handle, pipeline.handle, nullptr);

	log_info("The Pipeline was Destroyed.");
}
