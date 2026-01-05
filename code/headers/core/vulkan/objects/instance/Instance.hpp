#pragma once

#include <vulkan/vulkan.h>

#include <vector>

struct Instance {
    VkInstance handle = VK_NULL_HANDLE;
};

VkApplicationInfo instance_create_app_info();

VkInstanceCreateInfo instance_create_info(
    const VkApplicationInfo* app_info, 
    const VkDebugUtilsMessengerCreateInfoEXT* debug_info, 
    const std::vector<const char*>& exts
);

std::vector<const char*> instance_get_required_exts();

void instance_create(Instance* instance);

void instance_destroy(const Instance& instance);
