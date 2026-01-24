#include "core/vulkan/objects/pipeline/ShaderModule.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "util/debug/Logger.hpp"
#include "util/File.hpp"

#include <cstdint>

VkShaderModuleCreateInfo shader_module_create_info(const std::vector<char>& src) 
{
	log_info("Creating the Shader Module Info..."); 

	VkShaderModuleCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	create_info.codeSize = src.size();
	create_info.pCode = reinterpret_cast<const uint32_t*>(src.data());

	log_success("The Shader Module Info was Created!");

	return create_info;
}

void shader_module_create(shader_module_t* shader_module, const device_t& device, const std::string& path) 
{
	log_info("Creating a Shader Module...");

	const std::vector<char> src = read_file(path);
	VkShaderModuleCreateInfo shader_module_info = shader_module_create_info(src);

	if (vkCreateShaderModule(device.handle, &shader_module_info, nullptr, &shader_module->handle) != VK_SUCCESS) {
		log_critical("Failed to Create the ShaderModule!");
	}

	log_success("The Shader Module was Created!");
}

void shader_module_destroy(const shader_module_t& shader_module, const device_t& device) 
{
	log_info("Destroying the Shader Module...");

	if (shader_module.handle == VK_NULL_HANDLE) {
		log_error("Cannot Destroy the Shader Module::Shader Module is not Created!");
	}

	vkDestroyShaderModule(device.handle, shader_module.handle, nullptr);

	log_success("The Shader Module was Destroyed!");
}
