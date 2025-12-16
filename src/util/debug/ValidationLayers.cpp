#include "util/debug/ValidationLayers.hpp"
#include "util/debug/Logger.hpp"
#include "core/Core.hpp"

#include "fmt/core.h"
#include "fmt/color.h"

#include <vulkan/vulkan.h>

#include <vector>
#include <cstring>
#include <cstdint>

bool check_validation_layers_support() {
    uint32_t layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, nullptr);
    
    std::vector<VkLayerProperties> layers(layer_count);
    vkEnumerateInstanceLayerProperties(&layer_count, layers.data());
    
    for(const char* layer_name : validationLayers) {
        bool layerFound = false;
        for(const auto& layer_props: layers) {
            if(strcmp(layer_name, layer_props.layerName) == 0) {
                layerFound = true;
                break;
            }
        }
        if(!layerFound){
            return false;
        }
    }
    return true;
}

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
    fmt::print(fmt::fg(fmt::color::medium_purple), "{}\n", pcallback_data->pMessage);
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
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
    const VkAllocationCallbacks* pAllocator, 
    VkDebugUtilsMessengerEXT* pDebugMessenger
)
{    
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(Core::Core::get()->getInstance(), "vkCreateDebugUtilsMessengerEXT");
    if(func != nullptr) {
        func(Core::Core::get()->getInstance(), pCreateInfo, pAllocator, pDebugMessenger);
    }
    else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
    return VK_SUCCESS;
}

void debug_messenger_setup() {
    log_info("Creating a Debug Messenger...");
    
    VkDebugUtilsMessengerCreateInfoEXT debug_msgr_info = debug_msgr_create_info();
    VkDebugUtilsMessengerEXT debug_msgr;
    if(debug_msgr_create(&debug_msgr_info, nullptr, &debug_msgr) != VK_SUCCESS) {
        log_error("Failed to Create the Debug Messenger!");
    }
    else {
        log_success("The Debug Messenger was Created!");
    }
    return debug_msgr_info;
}
