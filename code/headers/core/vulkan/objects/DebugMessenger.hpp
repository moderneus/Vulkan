#include "core/vulkan/objects/Instance.hpp"

#include <vulkan/vulkan.h>

struct DebugMessenger {
    VkDebugUtilsMessengerEXT handle = VK_NULL_HANDLE;
};

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
