#include "core/vulkan/obj/pipeline/shader.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "util/debug/log.hpp"
#include "util/constants.hpp"
#include "util/file.hpp"

#include <cstdint>

VkShaderModuleCreateInfo shader_create_info(const std::vector<char> &src) 
{
	log_info("Creating the Shader Module Info..."); 

	VkShaderModuleCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	info.codeSize = src.size();
	info.pCode = reinterpret_cast<const uint32_t*>(src.data());

	log_info("The Shader Module Info was Created.");

	return info;
}

void shader_create(shader *shdr, const device &dev, const std::string &path) 
{
	log_info("Creating a Shader Module...");

	const std::vector<char> src = file_read(path);
	VkShaderModuleCreateInfo info = shader_create_info(src);

	if (vkCreateShaderModule(dev.handle, &info, nullptr, &shdr->handle) != VK_SUCCESS)
		log_critical("Failed to Create the ShaderModule.");

	log_info("The Shader Module was Created.");
}

void shader_destroy(const shader &shdr, const device &dev) 
{
	log_info("Destroying the Shader Module...");

	if (shdr.handle == VK_NULL_HANDLE)
		log_error("Cannot Destroy the Shader Module::Shader Module is not Created.");

	vkDestroyShaderModule(dev.handle, shdr.handle, nullptr);

	log_info("The Shader Module was Destroyed.");
}

void shaders_create(std::array<shader, 3> *shdrs, const device &dev) 
{
	log_info("Creating the Shader Modules...");

	for(uint32_t i = 0; i < shdrs->size(); ++i)
		shader_create(&shdrs->data()[i], dev, shdr_paths[i]);

	log_info("The Shader Modules were Created.");
}

void shaders_destroy(const std::array<shader, 3> &shdrs, const device &dev)
{
	log_info("Destroying the Shader Modules...");

	for(const auto &shdr : shdrs)
		vkDestroyShaderModule(dev.handle, shdr.handle, nullptr);

	log_info("The Shader Modules were Destroyed.");
}
