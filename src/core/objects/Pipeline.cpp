#include "core/objects/Pipeline.hpp"
#include "core/objects/ShaderModule.hpp"
#include "util/debug/Logger.hpp"
#include "util/File.hpp"

std::array<Engine::Core::ShaderModule, 2> Engine::Core::Pipeline::createShaderModules()
{
    
}

std::array<VkPipelineShaderStageCreateInfo, 2> Engine::Core::Pipeline::reateShaderStageInfo()
{
    
}

VkPipelineDynamicStateCreateInfo Engine::Core::Pipeline::createDynamicStateInfo()
{
    
}

VkPipelineVertexInputStateCreateInfo Engine::Core::Pipeline::createVertexInputInfo()
{
    
}

VkPipelineInputAssemblyStateCreateInfo createInputAssemblyInfo()
{
    
}

VkPipelineViewportStateCreateInfo createViewportInfo()
{
    
}

VkPipelineRasterizationStateCreateInfo createRasterizationInfo()
{
    
}

VkPipelineMultisampleStateCreateInfo createMultisampleInfo()
{
    
}

VkPipelineDepthStencilStateCreateInfo createDepthStencilInfo()
{
    
}

VkPipelineColorBlendStateCreateInfo createColorBlendInfo()
{
    
}

std::array<VkPipelineShaderStageCreateInfo, 2> Engine::Core::Pipeline::createShaderStageInfo(const std::array<Engine::Core::ShaderModule, 2>& shaderModules)
{
    Utils::Logger::get()->info("Creating the Pipeline Shader Stage Info...");
    
    std::array<VkPipelineShaderStageCreateInfo, 2> shaderStages;

    VkPipelineShaderStageCreateInfo vertCreateInfo = {};
    vertCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertCreateInfo.module = shaderModules[0].get();
    vertCreateInfo.pName = "main";

    shaderStages[0] = vertCreateInfo;

    VkPipelineShaderStageCreateInfo fragCreateInfo = {};
    fragCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragCreateInfo.module = shaderModules[1].get();
    fragCreateInfo.pName = "main";

    shaderStages[1] = fragCreateInfo;

    Utils::Logger::get()->success("The Pipeline Shader Stage Info was Created!");

    return shaderStages;
}

void Engine::Core::Pipeline::create(const LogicalDevice& device)
{
    
}

void Engine::Core::Pipeline::destroy(const LogicalDevice& device)
{
    Utils::Logger::get()->info("Destroying the Pipeline...");
    
    vertShaderModule.destroy(device);
    fragShaderModule.destroy(device);

    Utils::Logger::get()->success("The Pipeline was Destroyed!");
}

VkPipeline Engine::Core::Pipeline::get() const
{
    return pipeline;
}
