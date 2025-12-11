#include "core/objects/PipelineLayout.hpp"
#include "util/debug/Logger.hpp"
#include "util/File.hpp"
#include <vulkan/vulkan_core.h>


void Engine::Core::PipelineLayout::create(const LogicalDevice& device)
{
    Utils::Logger::get()->info("Creating a Pipeline Layout...");

 

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
