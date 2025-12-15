#include "core/objects/ShaderModule.hpp"
#include "util/debug/Logger.hpp"
#include "util/File.hpp"

#include <cstdint>

VkShaderModuleCreateInfo shader_module_create_info(const std::vector<char>& src) {
    Utils::Logger::get()->info("Creating the Shader Module Info..."); 
    VkShaderModuleCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    create_info.codeSize = src.size();
    create_info.pCode = reinterpret_cast<const uint32_t*>(src.data());
    Utils::Logger::get()->success("The Shader Module Info was Created!");
    return create_info;
}

void shader_module_create_info(ShaderModule* shader_module, const LogicalDevice& device, const std::string& path) {
    Utils::Logger::get()->info("Creating a Shader Module...");
    VkShaderModuleCreateInfo shader_module_info = shader_module_create_info();
    if(vkCreateShaderModule(device.handle, &shader_module_info, nullptr, &shader_module->handle) != VK_SUCCESS)
        Utils::Logger::get()->critical("Failed to Create the ShaderModule!");
    Utils::Logger::get()->success("The Shader Module was Created!");
}

void Engine::Core::ShaderModule::destroy(const ShaderModule& shader_module, const LogicalDevice& device) {
    Utils::Logger::get()->info("Destroying the Shader Module...");
    vkDestroyShaderModule(device.handle, shader_module.handle, nullptr);
    Utils::Logger::get()->success("The Shader Module was Destroyed!");
}
