#include "core/objects/PipelineLayout.hpp"
#include "util/debug/Logger.hpp"

#include <vulkan/vulkan.h>

VkPipelineLayoutCreateInfo Engine::Core::PipelineLayout::createInfo()
{
    VkPipelineLayoutCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    createInfo.setLayoutCount = 0;
    createInfo.pSetLayouts = nullptr;
    createInfo.pushConstantRangeCount = 0;

    return createInfo;
}

void Engine::Core::PipelineLayout::create(const LogicalDevice& device)
{
    Utils::Logger::get()->info("Creating a Pipeline Layout...");

    VkPipelineLayoutCreateInfo pipelineLayoutInfo = createInfo();

    if(vkCreatePipelineLayout(device.get(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
        Utils::Logger::get()->critical("Failed to Create the Pipeline Layout!");

    Utils::Logger::get()->success("The Pipeline Layout was Created!");
}

void Engine::Core::PipelineLayout::destroy(const LogicalDevice& device)
{
    Utils::Logger::get()->info("Destroying the Pipeline Layout...");
    
    if(pipelineLayout == VK_NULL_HANDLE)
        Utils::Logger::get()->error("Cannot Destroy the Pipeline Layout::Pipeline Layout is not Created!");
    
    vkDestroyPipelineLayout(device.get(), pipelineLayout, nullptr);

    Utils::Logger::get()->success("The Pipeline Layout was Destroyed!");
}
