#ifndef MOD_SHADER_HPP
#define MOD_SHADER_HPP

#include <vulkan/vulkan.h>

#include <string>
#include <vector>
#include <array>

struct device;

struct shader { 
	VkShaderModule handle = VK_NULL_HANDLE;
};

struct shader_reference {
	VkShaderModule handle = VK_NULL_HANDLE;
	VkShaderStageFlagBits stage;
};

VkShaderModuleCreateInfo shader_create_info(const std::vector<char>& src);

void shader_create(shader *shdr, const device &dev, const std::string &path);

void shader_destroy(const shader &shdr, const device &dev);

void shaders_create(std::array<shader, 3> *shdrs, const device &dev); 

void shaders_destroy(const std::array<shader, 3> &shdrs, const device &dev);

#endif
