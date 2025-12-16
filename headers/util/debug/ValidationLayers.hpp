#pragma once

#include <vulkan/vulkan.h>

#include <vector>

const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

bool check_validation_layers_support();

VKAPI_ATTR VkBool32 VKAPI_CALL callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallBackData,
    void* pUserData
);

VkDebugUtilsMessengerCreateInfoEXT debug_msgr_create_info();

VkResult debug_msgr_create(
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
    const VkAllocationCallbacks* pAllocator, 
    VkDebugUtilsMessengerEXT* pDebugMessenger
);

VkDebugUtilsMessengerCreateInfoEXT debug_msgr_setup();
