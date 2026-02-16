#include "core/vulkan/objects/pipeline/ShaderModule.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "util/debug/Logger.hpp"
#include "util/Constants.hpp"
#include "util/File.hpp"

#include <cstdint>

VkShaderModuleCreateInfo shdr_create_info(const std::vector<char> &src) 
{
	log_info("Creating the Shader Module Info..."); 

	VkShaderModuleCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	info.codeSize = src.size();
	info.pCode = reinterpret_cast<const uint32_t*>(src.data());

	log_info("The Shader Module Info was Created.");

	return info;
}

void shdr_create(shader_t *shdr, const device_t &dev, const std::string &path) 
{
	log_info("Creating a Shader Module...");

	const std::vector<char> src = file_read(path);
	VkShaderModuleCreateInfo info = shdr_create_info(src);

	if (vkCreateShaderModule(dev.handle, &info, nullptr, &shdr->handle) != VK_SUCCESS) {
		log_critical("Failed to Create the ShaderModule.");
	}

	log_info("The Shader Module was Created.");
}

void shdr_destroy(const shader_t &shdr, const device_t &dev) 
{
	log_info("Destroying the Shader Module...");

	if (shdr.handle == VK_NULL_HANDLE) {
		log_error("Cannot Destroy the Shader Module::Shader Module is not Created.");
	}

	vkDestroyShaderModule(dev.handle, shdr.handle, nullptr);

	log_info("The Shader Module was Destroyed.");
}

void shdrs_create(std::array<shader_t, 2> *shdrs, const device_t &dev) 
{
	log_info("Creating the Shader Modules...");

	for(uint32_t i = 0; i < shdrs->size(); ++i) {
		shdr_create(&shdrs->data()[i], dev, shdr_paths[i]);
	}

	log_info("The Shader Modules were Created.");
}

void shdrs_destroy(const std::array<shader_t, 2> &shdrs, const device_t &dev)
{
	log_info("Destroying the Shader Modules...");

	for(const auto &shdr : shdrs) {
		vkDestroyShaderModule(dev.handle, shdr.handle, nullptr);
	}

	log_info("The Shader Modules were Destroyed.");
}
