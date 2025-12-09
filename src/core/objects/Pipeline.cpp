#include "core/objects/Pipeline.hpp"
#include "util/File.hpp"

std::array<VkPipelineShaderStageCreateInfo, 2> Engine::Core::Pipeline::createShaderStageInfo(const LogicalDevice& device)
{
    std::array<VkPipelineShaderStageCreateInfo, 2> shaderStages;

    VkPipelineShaderStageCreateInfo vertCreateInfo = {};
    vertCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertCreateInfo.module = vertShaderModule.get();
    vertCreateInfo.pName = "main";

    shaderStages[0] = vertCreateInfo;

    VkPipelineShaderStageCreateInfo fragCreateInfo = {};
    fragCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragCreateInfo.module = fragShaderModule.get();
    fragCreateInfo.pName = "main";

    shaderStages[1] = fragCreateInfo;

    return shaderStages;
}

void Engine::Core::Pipeline::create(const LogicalDevice& device)
{
    auto vertSrc = Utils::readFile("shaders/vert/VertexShader.spv");
    vertShaderModule.create(device, vertSrc);

    auto fragSrc = Utils::readFile("shaders/frag/FragmentShader.spv");
    fragShaderModule.create(device, fragSrc);
}

void Engine::Core::Pipeline::destroy(const LogicalDevice& device)
{
    vertShaderModule.destroy(device);
    fragShaderModule.destroy(device);
}

VkPipeline Engine::Core::Pipeline::get() const
{
    return pipeline;
}