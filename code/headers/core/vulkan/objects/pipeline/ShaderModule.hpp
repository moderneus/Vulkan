#ifndef MOD_SHADER_MODULE_HPP
#define MOD_SHADER_MODULE_HPP

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

struct device_t;

struct shader_module_t 
{ 
	VkShaderModule handle = VK_NULL_HANDLE;
};

VkShaderModuleCreateInfo shader_module_create_info(const std::vector<char>& src);

void shader_module_create(shader_module_t* shader_module, const device_t& device, const std::string& path);

void shader_module_destroy(const shader_module_t& shader_module, const device_t& device);

#endif
