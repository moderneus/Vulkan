#ifndef MOD_SHADER_MODULE_HPP
#define MOD_SHADER_MODULE_HPP

#include <vulkan/vulkan.h>

#include <string>
#include <vector>
#include <array>

struct device_t;

struct shader_module_t 
{ 
	VkShaderModule handle = VK_NULL_HANDLE;
};

struct shader_module_ref_t
{
	VkShaderModule handle = VK_NULL_HANDLE;
	VkShaderStageFlagBits stage;
};

VkShaderModuleCreateInfo shader_module_create_info(const std::vector<char>& src);

void shader_module_create(shader_module_t* shader_module, const device_t& device, const std::string& path);

void shader_module_destroy(const shader_module_t& shader_module, const device_t& device);

void shader_modules_create(std::array<shader_module_t, 2>* shader_modules, const device_t& device); 

void shader_modules_destroy(const std::array<shader_module_t, 2>& shader_modules, const device_t& device);

#endif
