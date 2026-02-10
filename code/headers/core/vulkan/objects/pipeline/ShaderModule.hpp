#ifndef MOD_SHADER_HPP
#define MOD_SHADER_HPP

#include <vulkan/vulkan.h>

#include <string>
#include <vector>
#include <array>

struct device_t;

struct shader_t 
{ 
	VkShaderModule handle = VK_NULL_HANDLE;
};

struct shader_ref_t
{
	VkShaderModule handle = VK_NULL_HANDLE;
	VkShaderStageFlagBits stage;
};

VkShaderModuleCreateInfo shader_create_info(const std::vector<char>& src);

void shader_create(shader_t *shader, const device_t &dev, const std::string &path);

void shader_destroy(const shader_t &shader, const device_t &dev);

void shaders_create(std::array<shader_t, 2> *shaders, const device_t &dev); 

void shaders_destroy(const std::array<shader_t, 2> &shaders, const device_t &dev);

#endif
