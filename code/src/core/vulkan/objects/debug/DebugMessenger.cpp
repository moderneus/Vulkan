#include "core/vulkan/objects/debug/DebugMessenger.hpp"
#include "util/debug/Logger.hpp"

#include "fmt/core.h"
#include "fmt/color.h"

#include <vulkan/vulkan.h>

VKAPI_ATTR VkBool32 VKAPI_CALL callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT msg_severity,
    VkDebugUtilsMessageTypeFlagsEXT msg_type,
    const VkDebugUtilsMessengerCallbackDataEXT* pcallback_data,
    void* puser_data
)
{
    fmt::color color;
    switch(msg_severity) {
        default:
            color = fmt::color::white;
        break;
        
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            color = fmt::color::gray;
        break;

        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            color = fmt::color::gold;
        break;

        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            color = fmt::color::red;
        break;

        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            color = fmt::color::blue;
        break;
    }
    fmt::print(fmt::fg(fmt::color::dark_red), "[VULKAN] ");
    fmt::print(fmt::fg(color), "{}: ", pcallback_data->pMessageIdName);
    fmt::print(fmt::fg(fmt::color::white), "{}\n", pcallback_data->pMessage);
    return VK_FALSE;
}

VkDebugUtilsMessengerCreateInfoEXT debug_msgr_create_info() {
    log_info("Creating a Debug Messenger Info...");
    
    VkDebugUtilsMessengerCreateInfoEXT create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

    create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;
    
    create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    
    create_info.pfnUserCallback = callback;
    create_info.pUserData = nullptr;
    
    log_success("The Debug Messenger Info was created!");
    return create_info;
}

VkResult debug_msgr_create(
    const Instance& instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pcreate_info, 
    const VkAllocationCallbacks* pallocator, 
    DebugMessenger* debug_msgr 
) 
{    
    log_info("Creating a Debug Messenger...");
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance.handle, "vkCreateDebugUtilsMessengerEXT");
    if(func != nullptr) {
        func(instance.handle, pcreate_info, pallocator, &debug_msgr->handle);
    }
    else {
        log_error("Failed to Create the Debug Messegner::Extension not Present!");
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
    log_success("The Debug Messenger was Created!");
    return VK_SUCCESS;
}

VkResult debug_msgr_destroy(DebugMessenger* debug_msgr, const Instance& instance) {
    log_info("Destroying the Debug Messenger...");
    auto cleanup_func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance.handle, "vkDestroyDebugUtilsMessengerEXT");
    if(cleanup_func != nullptr) {
        cleanup_func(instance.handle, debug_msgr->handle, nullptr);
    }
    else {
        log_error("Failed to Destroy the Debug Messenger::Extension not Present!");
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
    log_success("The Debug Messenger was Destroyed!");
    return VK_SUCCESS;
}

void debug_msgr_setup(DebugMessenger* debug_msgr, const Instance& instance) {
    log_info("Setting up a Debug Messenger...");
    VkDebugUtilsMessengerCreateInfoEXT debug_msgr_info = debug_msgr_create_info();
    if(debug_msgr_create(instance, &debug_msgr_info, nullptr, debug_msgr) != VK_SUCCESS) {
        log_error("Failed to Create the Debug Messenger!");
    }
    log_success("The Debug Messenger was Setted up!");
}
