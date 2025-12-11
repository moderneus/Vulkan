#include "core/objects/ShaderModule.hpp"
#include "util/debug/Logger.hpp"
#include "util/File.hpp"

#include <cstdint>

VkShaderModuleCreateInfo Engine::Core::ShaderModule::createInfo(const std::vector<char>& src)
{
    Utils::Logger::get()->info("Creating the Shader Module Info...");
    
    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = src.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(src.data());

    Utils::Logger::get()->success("The Shader Module Info was Created!");

    return createInfo;
}

void Engine::Core::ShaderModule::create(const LogicalDevice& device, const std::string& path)
{
    Utils::Logger::get()->info("Creating a Shader Module...");
    
    VkShaderModuleCreateInfo shaderModuleInfo = createInfo(Utils::readFile(path));

    if(vkCreateShaderModule(device.get(), &shaderModuleInfo, nullptr, &shaderModule) != VK_SUCCESS)
        Utils::Logger::get()->critical("Failed to Create the ShaderModule!");
    
    Utils::Logger::get()->success("The Shader Module was Created!");
}

void Engine::Core::ShaderModule::destroy(const LogicalDevice& device)
{
    Utils::Logger::get()->info("Destroying the Shader Module...");
    
    vkDestroyShaderModule(device.get(), shaderModule, nullptr);

    Utils::Logger::get()->success("The Shader Module was Destroyed!");
}

VkShaderModule Engine::Core::ShaderModule::get() const
{
    return shaderModule;
}
