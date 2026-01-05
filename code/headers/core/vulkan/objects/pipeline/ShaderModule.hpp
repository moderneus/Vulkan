#pragma once

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

struct LogicalDevice;

struct ShaderModule { 
    VkShaderModule handle = VK_NULL_HANDLE;
};

VkShaderModuleCreateInfo shader_module_create_info(const std::vector<char>& src);

void shader_module_create(ShaderModule* shader_module, const LogicalDevice& device, const std::string& path);

void shader_module_destroy(const ShaderModule& shader_module, const LogicalDevice& device);
