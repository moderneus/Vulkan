#include "core/objects/ShaderModule.hpp"
#include "util/debug/Logger.hpp"

#include <cstdint>

VkShaderModuleCreateInfo Engine::Core::ShaderModule::createInfo(const std::vector<char>& src)
{
    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = src.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(src.data());

    return createInfo;
}

void Engine::Core::ShaderModule::create(const LogicalDevice& device, const std::vector<char>& src)
{
    VkShaderModuleCreateInfo shaderModuleInfo = createInfo(src);

    if(vkCreateShaderModule(device.get(), &shaderModuleInfo, nullptr, &shaderModule) != VK_SUCCESS)
        Utils::Logger::get()->critical("Failed to Create the ShaderModule!");
}

void Engine::Core::ShaderModule::destroy(const LogicalDevice& device)
{
    vkDestroyShaderModule(device.get(), shaderModule, nullptr);
}

VkShaderModule Engine::Core::ShaderModule::get() const
{
    return shaderModule;
}