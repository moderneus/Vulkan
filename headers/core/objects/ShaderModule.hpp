#pragma once

#include "core/objects/LogicalDevice.hpp"

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

struct ShaderModule { 
    VkShaderModule handle = VK_NULL_HANDLE;
};

VkShaderModuleCreateInfo shader_module_create_info(const std::vector<char>& src);

void shader_module_create(const LogicalDevice& device, const std::string& path);

void shader_module_destroy(const LogicalDevice& device);
