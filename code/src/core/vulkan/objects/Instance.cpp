#include "core/vulkan/objects/Instance.hpp"
#include "util/String.hpp"
#include "util/debug/ValidationLayers.hpp"
#include "util/debug/Logger.hpp"

#include "SDL3/SDL_vulkan.h"

#include <vulkan/vulkan.h>

#include <cstdint>

std::vector<const char*> instance_get_required_exts() {
    uint32_t exts_count = 0;
    const char* const* exts;
    exts = SDL_Vulkan_GetInstanceExtensions(&exts_count);
    
    std::vector<const char*> exts_vec(exts, exts + exts_count);
    exts_vec.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    
    log_info("Extensions = ", cstr_vec_to_str_vec(exts_vec));
    log_info("Extensions count = " + std::to_string(exts_count));
    return exts_vec;
}

VkApplicationInfo instance_create_app_info() {
    log_info("Creating an Application Info...");
    
    VkApplicationInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    create_info.pApplicationName = "Vulkan";
    create_info.applicationVersion = VK_MAKE_VERSION(0, 0, 2);
    create_info.pEngineName = "No Engine";
    create_info.engineVersion = VK_MAKE_VERSION(0, 0, 2);
    create_info.apiVersion = VK_API_VERSION_1_4;
    
    log_success("The Application Info created!");
    return create_info;
}

VkInstanceCreateInfo instance_create_info(
    const VkApplicationInfo* app_info, 
    const VkDebugUtilsMessengerCreateInfoEXT* debug_info, 
    const std::vector<const char*>& exts
) 
{
    log_info("Creating the Instance Info...");
    
    VkInstanceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pNext = nullptr;
    create_info.pApplicationInfo = app_info;
    create_info.enabledExtensionCount = static_cast<uint32_t>(exts.size());
    create_info.ppEnabledExtensionNames = reinterpret_cast<const char* const*>(exts.data());
    
    log_info("Checking Valiation Layers Support...");
    
    if(check_validation_layers_support()){
        log_success("Validation layers is support!");
        create_info.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        create_info.ppEnabledLayerNames = validationLayers.data();
        create_info.pNext = debug_info;
    }
    else {
        log_error("Validation Layers doesn't support!");
        create_info.enabledLayerCount = 0;
        create_info.ppEnabledLayerNames = nullptr;
    }
    log_success("The Instance info was created!");
    return create_info;
}

void instance_create(Instance* instance) {
    log_info("Creating an Instance...");
    
    VkApplicationInfo app_info = instance_create_app_info();
    VkDebugUtilsMessengerCreateInfoEXT debug_info = debug_msgr_create_info();
    std::vector<const char*> exts = instance_get_required_exts();
    VkInstanceCreateInfo instance_info = instance_create_info(&app_info, &debug_info, exts);
    
    VkResult res = vkCreateInstance(&instance_info, nullptr, &instance->handle);
    if(res != VK_SUCCESS) {
        log_critical("The Instance creation Failed::" + std::to_string(res));
    }
    log_success("The Instance was Created!");
}

void instance_destroy(const Instance& instance) {
    log_info("Destroying the Instance...");
    if(instance.handle == VK_NULL_HANDLE) {
        log_error("Cannot Destroy the Instance::Instance is not Created!");
    }
    vkDestroyInstance(instance.handle, nullptr);
    log_success("The Instance was Destroyed!");
}
