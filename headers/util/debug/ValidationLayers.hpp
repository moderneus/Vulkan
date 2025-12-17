#pragma once

#include "core/vulkan/objects/Instance.hpp"

#include <vulkan/vulkan.h>

#include <vector>

struct DebugMessenger {
    VkDebugUtilsMessengerEXT msgr = VK_NULL_HANDLE;
};

const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

bool check_validation_layers_support();

VKAPI_ATTR VkBool32 VKAPI_CALL callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT msg_severity,
    VkDebugUtilsMessageTypeFlagsEXT msg_type,
    const VkDebugUtilsMessengerCallbackDataEXT* pcallback_data,
    void* puser_data 
);

VkDebugUtilsMessengerCreateInfoEXT debug_msgr_create_info();

VkResult debug_msgr_create(
    const Instance& instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pcreate_info, 
    const VkAllocationCallbacks* pallocator, 
    DebugMessenger* debug_msgr 
);

VkResult debug_msgr_destroy(DebugMessenger* debug_msgr, const Instance& instance);

void debug_msgr_setup(DebugMessenger* debug_mgsr, const Instance& instance);
