#include "core/objects/Pipeline.hpp"
#include "core/objects/ShaderModule.hpp"
#include "util/debug/Logger.hpp"

VkViewport pipeline_create_viewport(const Swapchain& swapchain) {
    VkViewport viewport = {};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(swapchain.extent.width);
    viewport.height = static_cast<float>(swapchain.extent.height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    return viewport;
}

VkRect2D pipeline_create_scissor(const Swapchain& swapchain) {
    VkRect2D scissor = {};
    scissor.offset = {0, 0};
    scissor.extent = swapchain.extent;
    return scissor;
}

void pipeline_create_shader_modules(Pipeline* pipeline, const LogicalDevice& device) {
    shader_module_create(&pipeline->vert_shader, device, "shaders/vert/VertexShader.spv");
    shader_module_create(&pipeline->frag_shader, device, "shaders/frag/FragmentShader.spv");
}

std::array<VkPipelineShaderStageCreateInfo, 2> pipeline_create_shader_stage_info(const Pipeline& pipeline) {
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
    
    return {vertex_shader_stage_create_info, fragment_shader_stage_create_info};
}

VkPipelineDynamicStateCreateInfo pipeline_create_dynamic_state_info() {
    std::vector<VkDynamicState> dynamic_state = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
    VkPipelineDynamicStateCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    create_info.dynamicStateCount = static_cast<uint32_t>(dynamic_state.size());
    create_info.pDynamicStates = dynamic_state.data();
    return create_info;
}

VkPipelineVertexInputStateCreateInfo pipeline_create_vertex_input_info() {
    VkPipelineVertexInputStateCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    create_info.vertexBindingDescriptionCount = 0;
    create_info.pVertexBindingDescriptions = nullptr;
    create_info.vertexAttributeDescriptionCount = 0;
    create_info.pVertexAttributeDescriptions = nullptr;
    return create_info;
}

VkPipelineInputAssemblyStateCreateInfo pipeline_create_input_assembly_info() {
    VkPipelineInputAssemblyStateCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    create_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    create_info.primitiveRestartEnable = VK_FALSE;
    return create_info;
}

VkPipelineViewportStateCreateInfo pipeline_create_viewport_info(const VkViewport& viewport, const VkRect2D& scissor) {
    VkPipelineViewportStateCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    create_info.viewportCount = 1;
    create_info.pViewports = &viewport;
    create_info.scissorCount = 1;
    create_info.pScissors = &scissor;
    return create_info;
}

VkPipelineRasterizationStateCreateInfo pipeline_create_rasterization_info() {
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
    return create_info;
}

VkPipelineMultisampleStateCreateInfo pipeline_create_multisample_info() {
    VkPipelineMultisampleStateCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    create_info.sampleShadingEnable = VK_FALSE;
    create_info.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    return create_info;
}

VkPipelineDepthStencilStateCreateInfo pipeline_create_depth_stencil_info() {
    
}

VkPipelineColorBlendStateCreateInfo pipeline_create_color_blend_info() {
    VkPipelineColorBlendAttachmentState attachment = {};
    attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    attachment.blendEnable = VK_FALSE;
    VkPipelineColorBlendStateCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    create_info.logicOpEnable = VK_FALSE;
    create_info.attachmentCount = 1;
    create_info.pAttachments = &attachment;
    return create_info;
}

void pipeline_create(const LogicalDevice& device, const Swapchain& swapchain) {
    
}

void pipeline_destroy(const Pipeline& pipeline, const LogicalDevice& device) {
    log_info("Destroying the Pipeline...");
    shader_module_destroy(pipeline.vert_shader, device);
    shader_module_destroy(pipeline.frag_shader, device);
    log_success("The Pipeline was Destroyed!");
}
