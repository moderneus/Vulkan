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

VkShaderModuleCreateInfo shdr_create_info(const std::vector<char>& src);

void shdr_create(shader_t *shdr, const device_t &dev, const std::string &path);

void shdr_destroy(const shader_t &shdr, const device_t &dev);

void shdrs_create(std::array<shader_t, 2> *shdrs, const device_t &dev); 

void shdrs_destroy(const std::array<shader_t, 2> &shdrs, const device_t &dev);

#endif
