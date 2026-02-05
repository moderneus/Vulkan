#include "core/vulkan/objects/pipeline/Pipeline.hpp"
#include "core/vulkan/objects/pipeline/PipelineLayout.hpp"
#include "core/vulkan/objects/pipeline/ShaderModule.hpp"
#include "core/vulkan/objects/swapchain/Swapchain.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "core/vulkan/objects/renderpass/RenderPass.hpp"
#include "core/vulkan/objects/buffers/types/Vertex.hpp"
#include "util/debug/Logger.hpp"

VkViewport pipeline_create_viewport(const swapchain_state_t& st) 
{
	VkViewport viewport = {};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = static_cast<float>(st.extent.width);
	viewport.height = static_cast<float>(st.extent.height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	return viewport;
}

VkRect2D pipeline_create_scissor(const swapchain_state_t& st) 
{
	VkRect2D scissor = {};
	scissor.offset = {0, 0};
	scissor.extent = st.extent;
	return scissor;
}

VkPipelineColorBlendAttachmentState pipeline_create_color_blend_attachment() 
{
	log_info("Creating a Color Blend Attachment...");

	VkPipelineColorBlendAttachmentState attachment = {};

	attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | 
				    VK_COLOR_COMPONENT_G_BIT | 
				    VK_COLOR_COMPONENT_B_BIT | 
				    VK_COLOR_COMPONENT_A_BIT;

	attachment.blendEnable = VK_FALSE;
	attachment.alphaBlendOp = VK_BLEND_OP_ADD;
	
	log_info("The Color Blend Attachment was Created.");

	return attachment;
}

std::vector<shader_module_ref_t> pipeline_create_shader_module_refs(const std::array<shader_module_t, 2>& shader_modules)
{
	log_info("Creating the Shader Modules References...");

	std::vector<shader_module_ref_t> shader_module_refs;
	shader_module_refs.push_back({shader_modules[0].handle, VK_SHADER_STAGE_VERTEX_BIT});
	shader_module_refs.push_back({shader_modules[1].handle, VK_SHADER_STAGE_FRAGMENT_BIT});
	return shader_module_refs;

	log_info("The Shader Module References were Created.");
}

VkPipelineShaderStageCreateInfo pipeline_create_shader_stage_info(const shader_module_ref_t& shader_module) 
{
	log_info("Creating the Shader Stage Info...");

	VkPipelineShaderStageCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	create_info.stage = shader_module.stage;
	create_info.module = shader_module.handle;
	create_info.pName = "main";

	log_info("The Shader Stage Info was Created.");

	return create_info;
}

std::vector<VkPipelineShaderStageCreateInfo> pipeline_create_shader_stage_infos(const pipeline_config_t& cfg)
{
	log_info("Creating the Shader Stage Infos...");

	std::vector<VkPipelineShaderStageCreateInfo> shader_stage_infos;
	for(const auto& shader_module : cfg.shader_module_refs) {
		shader_stage_infos.push_back(pipeline_create_shader_stage_info(shader_module));
	}
	return shader_stage_infos;

	log_info("The Shader Stage Infos were Created!");
}

VkPipelineDynamicStateCreateInfo pipeline_create_dynamic_state_info(const std::vector<VkDynamicState>& dynamic_state) 
{
	log_info("Creating a Dynamic State Info...");

	VkPipelineDynamicStateCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	create_info.dynamicStateCount = static_cast<uint32_t>(dynamic_state.size());
	create_info.pDynamicStates = dynamic_state.data();

	log_info("The Dynamic State Info was Created.");

	return create_info;
}

VkPipelineVertexInputStateCreateInfo pipeline_create_vertex_input_info(const pipeline_config_t& cfg) 
{
	log_info("Creating a Vertex Input Info...");

	VkPipelineVertexInputStateCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	create_info.vertexBindingDescriptionCount = 1;
	create_info.pVertexBindingDescriptions = &cfg.binding_description;
	create_info.vertexAttributeDescriptionCount = static_cast<uint32_t>(cfg.attrib_description.size());
	create_info.pVertexAttributeDescriptions = cfg.attrib_description.data();

	log_info("The Vertex Input Info was Created.");

	return create_info;
}

VkPipelineInputAssemblyStateCreateInfo pipeline_create_input_assembly_info() 
{
	log_info("Creating a Input Assembly Info...");

	VkPipelineInputAssemblyStateCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	create_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	create_info.primitiveRestartEnable = VK_FALSE;

	log_info("The Input Assembly Info was Created.");

	return create_info;
}

VkPipelineViewportStateCreateInfo pipeline_create_viewport_info(const VkViewport& viewport, const VkRect2D& scissor) 
{
	log_info("Creating the Viewport Info...");

	VkPipelineViewportStateCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	create_info.viewportCount = 1;
	create_info.pViewports = &viewport;
	create_info.scissorCount = 1;
	create_info.pScissors = &scissor;

	log_info("The Viewport Info was Created.");

	return create_info;
}

VkPipelineRasterizationStateCreateInfo pipeline_create_rasterization_info() 
{
	log_info("Creating a Rasterization Info...");

	VkPipelineRasterizationStateCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	create_info.depthClampEnable = VK_FALSE;
	create_info.rasterizerDiscardEnable = VK_FALSE;
	create_info.polygonMode = VK_POLYGON_MODE_FILL;
	create_info.lineWidth = 1.0f;
	create_info.cullMode = VK_CULL_MODE_BACK_BIT;
	create_info.frontFace = VK_FRONT_FACE_CLOCKWISE;
	create_info.depthBiasEnable = VK_FALSE;
	create_info.depthBiasConstantFactor = 0.0f;
	create_info.depthBiasClamp = 0.0f;
	create_info.depthBiasSlopeFactor = 0.0f;

	log_info("The Rasterization Info was Created.");

	return create_info;
}

VkPipelineMultisampleStateCreateInfo pipeline_create_multisample_info() 
{
	log_info("Creating a Multisampling Info...");

	VkPipelineMultisampleStateCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	create_info.sampleShadingEnable = VK_FALSE;
	create_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	log_info("The Multisampling Info was Created.");

	return create_info;
}

#if 0
VkPipelineDepthStencilStateCreateInfo pipeline_create_depth_stencil_info() {
    
}
#endif

VkPipelineColorBlendStateCreateInfo pipeline_create_color_blend_info(const VkPipelineColorBlendAttachmentState* attachment) 
{
	log_info("Creating the Color Blend Info...");

	VkPipelineColorBlendStateCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	create_info.logicOpEnable = VK_FALSE;
	create_info.attachmentCount = 1;
	create_info.pAttachments = attachment;

	log_info("The Color Blend Info was Created.");

	return create_info;
}

VkGraphicsPipelineCreateInfo pipeline_create_info(const pipeline_info_t& info, const pipeline_layout_t& pipeline_layout, const render_pass_t& render_pass)
{
	log_info("Creating the Pipeline Info...");

	VkGraphicsPipelineCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	create_info.stageCount = 2;
	create_info.pStages = info.shader_stage_info.data();
	create_info.pVertexInputState = &info.vertex_input_info;
	create_info.pInputAssemblyState = &info.input_assembly_info;
	create_info.pViewportState = &info.viewport_info;
	create_info.pRasterizationState = &info.rasterization_info;
	create_info.pMultisampleState = &info.multisample_info;
	create_info.pDepthStencilState = nullptr;
	create_info.pColorBlendState = &info.color_blend_info;
	create_info.pDynamicState = &info.dynamic_state_info;
	create_info.layout = pipeline_layout.handle;
	create_info.renderPass = render_pass.handle;
	create_info.subpass = 0;

	log_info("The Pipeline Info was Created.");

	return create_info;
}

void pipeline_create(pipeline_t* pipeline, const device_t& device, const swapchain_state_t& st, const pipeline_layout_t& pipeline_layout, const render_pass_t& render_pass, const std::array<shader_module_t, 2> shader_modules) 
{
	log_info("Creating a Pipeline...");

	pipeline_config_t cfg = {};
	cfg.shader_module_refs = pipeline_create_shader_module_refs(shader_modules);
	cfg.viewport = pipeline_create_viewport(st);
	cfg.scissor = pipeline_create_scissor(st);
	cfg.attachment = pipeline_create_color_blend_attachment();
	cfg.binding_description = vertex_get_binding_description();
	cfg.attrib_description = vertex_get_attrib_description();

	pipeline_info_t info = {};
	info.shader_stage_info = pipeline_create_shader_stage_infos(cfg);
	info.vertex_input_info = pipeline_create_vertex_input_info(cfg);
	info.input_assembly_info = pipeline_create_input_assembly_info();
	info.viewport_info = pipeline_create_viewport_info(cfg.viewport, cfg.scissor);
	info.rasterization_info = pipeline_create_rasterization_info();
	info.multisample_info = pipeline_create_multisample_info();
	info.color_blend_info = pipeline_create_color_blend_info(&cfg.attachment);
	info.dynamic_state_info = pipeline_create_dynamic_state_info(cfg.dynamic_states);

	VkGraphicsPipelineCreateInfo pipeline_info = pipeline_create_info(info, pipeline_layout, render_pass);

	if (vkCreateGraphicsPipelines(device.handle, VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &pipeline->handle) != VK_SUCCESS) {
		log_critical("Failed to Create the Graphics Pipeline.");
	}

	log_info("The Pipeline was Created.");
}

void pipeline_destroy(const pipeline_t& pipeline, const device_t& device) 
{
	log_info("Destroying the Pipeline...");

	if (pipeline.handle == VK_NULL_HANDLE) {
		log_error("Cannot Destroy the Pipeline::Pipeline is not Created.");
	}

	vkDestroyPipeline(device.handle, pipeline.handle, nullptr);

	log_info("The Pipeline was Destroyed.");
}
