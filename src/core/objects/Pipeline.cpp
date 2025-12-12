#include "core/objects/Pipeline.hpp"
#include "core/objects/ShaderModule.hpp"
#include "util/debug/Logger.hpp"

VkViewport Engine::Core::Pipeline::createViewport(const Swapchain& swapchain)
{
    VkViewport viewport = {};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(swapchain.extent().width);
    viewport.height = static_cast<float>(swapchain.extent().height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    return viewport;
}

VkRect2D Engine::Core::Pipeline::createScissor(const Swapchain& swapchain)
{
    VkRect2D scissor = {};
    scissor.offset = {0, 0};
    scissor.extent = swapchain.extent();
    
    return scissor;
}

void Engine::Core::Pipeline::createShaderModules(const LogicalDevice& device)
{
    vertexShader.create(device, "shaders/vert/VertexShader.spv");
    fragmentShader.create(device, "shaders/frag/FragmentShader.spv");
}

std::array<VkPipelineShaderStageCreateInfo, 2> Engine::Core::Pipeline::createShaderStageInfo()
{
    VkPipelineShaderStageCreateInfo vertexShaderStageInfo = {};
    vertexShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertexShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertexShaderStageInfo.module = vertexShader.get();
    vertexShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragmentShaderStageInfo = {};
    fragmentShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragmentShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragmentShaderStageInfo.module = fragmentShader.get();
    fragmentShaderStageInfo.pName = "main";

    return {vertexShaderStageInfo, fragmentShaderStageInfo};
}

VkPipelineDynamicStateCreateInfo Engine::Core::Pipeline::createDynamicStateInfo()
{
    std::vector<VkDynamicState> dynamicState = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};

    VkPipelineDynamicStateCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    createInfo.dynamicStateCount = static_cast<uint32_t>(dynamicState.size());
    createInfo.pDynamicStates = dynamicState.data();
    
    return createInfo;
}

VkPipelineVertexInputStateCreateInfo Engine::Core::Pipeline::createVertexInputInfo()
{
    VkPipelineVertexInputStateCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    createInfo.vertexBindingDescriptionCount = 0;
    createInfo.pVertexBindingDescriptions = nullptr;
    createInfo.vertexAttributeDescriptionCount = 0;
    createInfo.pVertexAttributeDescriptions = nullptr;

    return createInfo;
}

VkPipelineInputAssemblyStateCreateInfo createInputAssemblyInfo()
{
    VkPipelineInputAssemblyStateCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    createInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    createInfo.primitiveRestartEnable = VK_FALSE;

    return createInfo;
}

VkPipelineViewportStateCreateInfo createViewportInfo(const VkViewport& viewport, const VkRect2D& scissor)
{
    VkPipelineViewportStateCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    createInfo.viewportCount = 1;
    createInfo.pViewports = &viewport;
    createInfo.scissorCount = 1;
    createInfo.pScissors = &scissor;

    return createInfo;
}

VkPipelineRasterizationStateCreateInfo createRasterizationInfo()
{
    VkPipelineRasterizationStateCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    createInfo.depthClampEnable = VK_FALSE;
    createInfo.rasterizerDiscardEnable = VK_FALSE;
    createInfo.polygonMode = VK_POLYGON_MODE_FILL;
    createInfo.lineWidth = 1.0f;
    createInfo.cullMode = VK_CULL_MODE_BACK_BIT;
    createInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
    createInfo.depthBiasEnable = VK_FALSE;
    createInfo.depthBiasConstantFactor = 0.0f;
    createInfo.depthBiasClamp = 0.0f;
    createInfo.depthBiasSlopeFactor = 0.0f;

    return createInfo;
}

VkPipelineMultisampleStateCreateInfo createMultisampleInfo()
{
    VkPipelineMultisampleStateCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    createInfo.sampleShadingEnable = VK_FALSE;
    createInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    return createInfo;
}

VkPipelineDepthStencilStateCreateInfo createDepthStencilInfo()
{
}

VkPipelineColorBlendStateCreateInfo createColorBlendInfo()
{
    VkPipelineColorBlendAttachmentState attachment = {};
    attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    attachment.blendEnable = VK_FALSE;
    
    VkPipelineColorBlendStateCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    createInfo.logicOpEnable = VK_FALSE;
    createInfo.attachmentCount = 1;
    createInfo.pAttachments = &attachment;

    return createInfo;
}

void Engine::Core::Pipeline::create(const LogicalDevice& device, const Swapchain& swapchain)
{
    
}

void Engine::Core::Pipeline::destroy(const LogicalDevice& device)
{
    Utils::Logger::get()->info("Destroying the Pipeline...");
    
    vertexShader.destroy(device);
    fragmentShader.destroy(device);

    Utils::Logger::get()->success("The Pipeline was Destroyed!");
}

VkPipeline Engine::Core::Pipeline::get() const
{
    return pipeline;
}
