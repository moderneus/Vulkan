#include "core/vulkan/objects/pipeline/Pipeline.hpp"
#include "core/vulkan/objects/pipeline/PipelineLayout.hpp"
#include "core/vulkan/objects/pipeline/ShaderModule.hpp"
#include "core/vulkan/objects/swapchain/Swapchain.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "core/vulkan/objects/renderpass/RenderPass.hpp"
#include "util/debug/Logger.hpp"

VkViewport pipeline_create_viewport(const swapchain_t& swapchain) 
{
	VkViewport viewport = {};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = static_cast<float>(swapchain.extent.width);
	viewport.height = static_cast<float>(swapchain.extent.height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	return viewport;
}

VkRect2D pipeline_create_scissor(const swapchain_t& swapchain) 
{
	VkRect2D scissor = {};
	scissor.offset = {0, 0};
	scissor.extent = swapchain.extent;
	return scissor;
}

void pipeline_create_shader_modules(pipeline_t* pipeline, const device_t& device) 
{
	shader_module_create(&pipeline->vert_shader, device, "shaders/vert/VertexShader.spv");
	shader_module_create(&pipeline->frag_shader, device, "shaders/frag/FragmentShader.spv");
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
	
	log_success("The Color Blend Attachment was Created!");

	return attachment;
}

std::array<VkPipelineShaderStageCreateInfo, 2> pipeline_create_shader_stage_info(const pipeline_t& pipeline) 
{
	log_info("Creating a Shader Stage Info...");

	VkPipelineShaderStageCreateInfo vertex_shader_stage_create_info = {};
	vertex_shader_stage_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertex_shader_stage_create_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertex_shader_stage_create_info.module = pipeline.vert_shader.handle;
	vertex_shader_stage_create_info.pName = "main";

	VkPipelineShaderStageCreateInfo fragment_shader_stage_create_info = {};
	fragment_shader_stage_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragment_shader_stage_create_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragment_shader_stage_create_info.module = pipeline.frag_shader.handle;
	fragment_shader_stage_create_info.pName = "main";

	log_success("The Shader Stage Info was Created!");

	return {vertex_shader_stage_create_info, fragment_shader_stage_create_info};
}

VkPipelineDynamicStateCreateInfo pipeline_create_dynamic_state_info(const std::vector<VkDynamicState>& dynamic_state) 
{
	log_info("Creating a Dynamic State Info...");

	VkPipelineDynamicStateCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	create_info.dynamicStateCount = static_cast<uint32_t>(dynamic_state.size());
	create_info.pDynamicStates = dynamic_state.data();

	log_success("The Dynamic State Info was Created!");

	return create_info;
}

VkPipelineVertexInputStateCreateInfo pipeline_create_vertex_input_info() 
{
	log_info("Creating a Vertex Input Info...");

	VkPipelineVertexInputStateCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	create_info.vertexBindingDescriptionCount = 0;
	create_info.pVertexBindingDescriptions = nullptr;
	create_info.vertexAttributeDescriptionCount = 0;
	create_info.pVertexAttributeDescriptions = nullptr;

	log_success("The Vertex Input Info was Created!");

	return create_info;
}

VkPipelineInputAssemblyStateCreateInfo pipeline_create_input_assembly_info() 
{
	log_info("Creating a Input Assembly Info...");

	VkPipelineInputAssemblyStateCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	create_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	create_info.primitiveRestartEnable = VK_FALSE;

	log_success("The Input Assembly Info was Created!");

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

	log_success("The Viewport Info was Created!");

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

	log_success("The Rasterization Info was Created!");

	return create_info;
}

VkPipelineMultisampleStateCreateInfo pipeline_create_multisample_info() 
{
	log_info("Creating a Multisampling Info...");
	VkPipelineMultisampleStateCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	create_info.sampleShadingEnable = VK_FALSE;
	create_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	log_success("The Multisampling Info was Created!");
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

	log_success("The Color Blend Info was Created!");

	return create_info;
}

VkGraphicsPipelineCreateInfo pipeline_create_info(const pipeline_state_t &state, const pipeline_layout_t& pipeline_layout, const render_pass_t& render_pass)
{
	log_info("Creating the Pipeline Info...");

	VkGraphicsPipelineCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	create_info.stageCount = 2;
	create_info.pStages = state.shader_stages.data();
	create_info.pVertexInputState = &state.vertex_input_info;
	create_info.pInputAssemblyState = &state.input_assembly_info;
	create_info.pViewportState = &state.viewport_info;
	create_info.pRasterizationState = &state.rasterization_info;
	create_info.pMultisampleState = &state.multisample_info;
	create_info.pDepthStencilState = nullptr;
	create_info.pColorBlendState = &state.color_blend_info;
	create_info.pDynamicState = &state.dynamic_state_info;
	create_info.layout = pipeline_layout.handle;
	create_info.renderPass = render_pass.handle;
	create_info.subpass = 0;

	log_success("The Pipeline Info was Created!");

	return create_info;
}

void pipeline_create(pipeline_t* pipeline, const device_t& device, const swapchain_t& swapchain, const pipeline_layout_t& pipeline_layout, const render_pass_t& render_pass) 
{
	log_info("Creating a Pipeline...");

	pipeline_create_shader_modules(pipeline, device);

	pipeline_state_t state = {};
	state.shader_stages = pipeline_create_shader_stage_info(*pipeline);
	state.vertex_input_info = pipeline_create_vertex_input_info();
	state.input_assembly_info = pipeline_create_input_assembly_info();
	VkViewport viewport = pipeline_create_viewport(swapchain);
	VkRect2D scissor = pipeline_create_scissor(swapchain);
	state.viewport_info = pipeline_create_viewport_info(viewport, scissor);
	state.rasterization_info = pipeline_create_rasterization_info();
	state.multisample_info = pipeline_create_multisample_info();
	VkPipelineColorBlendAttachmentState attachment = pipeline_create_color_blend_attachment();
	state.color_blend_info = pipeline_create_color_blend_info(&attachment);
	std::vector<VkDynamicState> dynamic_state = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
	state.dynamic_state_info = pipeline_create_dynamic_state_info(dynamic_state);

	VkGraphicsPipelineCreateInfo pipeline_info = pipeline_create_info(state, pipeline_layout, render_pass);

	if (vkCreateGraphicsPipelines(device.handle, VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &pipeline->handle) != VK_SUCCESS) {
		log_critical("Failed to Create the Graphics Pipeline!");
	}

	log_success("The Pipeline was Created!");
}

void pipeline_destroy(const pipeline_t& pipeline, const device_t& device) 
{
	log_info("Destroying the Pipeline...");

	shader_module_destroy(pipeline.vert_shader, device);
	shader_module_destroy(pipeline.frag_shader, device);

	if (pipeline.handle == VK_NULL_HANDLE) {
		log_error("Cannot Destroy the Pipeline::Pipeline is not Created!");
	}

	vkDestroyPipeline(device.handle, pipeline.handle, nullptr);

	log_success("The Pipeline was Destroyed!");
}
