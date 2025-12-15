#include "core/objects/Instance.hpp"
#include "util/String.hpp"
#include "util/debug/ValidationLayers.hpp"
#include "util/debug/Logger.hpp"

#include "SDL3/SDL_vulkan.h"

#include <vulkan/vulkan.h>

#include <cstdint>
#include <vulkan/vulkan_core.h>

std::vector<const char*> instance_get_required_exts() {
    uint32_t exts_count = 0;
    const char* const* exts;
    exts = SDL_Vulkan_GetInstanceExtensions(&exts_count);
    std::vector<const char*> exts_vec(exts, exts + exts_count);
    exts_vec.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    Utils::Logger::get()->info("Extensions = ", Utils::cstrVectorToStringVector(exts_vec));
    Utils::Logger::get()->info("Extensions count = " + std::to_string(exts_count));
    return exts_vec;
}

VkApplicationInfo instane_create_app_info() {
    Utils::Logger::get()->info("Creating an Application Info...");
    VkApplicationInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    create_info.pApplicationName = "Vulkan";
    create_info.applicationVersion = VK_MAKE_VERSION(0, 0, 2);
    create_info.pEngineName = "No Engine";
    create_info.engineVersion = VK_MAKE_VERSION(0, 0, 2);
    create_info.apiVersion = VK_API_VERSION_1_4;
    Utils::Logger::get()->success("The Application Info created!");
    return create_info;
}

VkInstanceCreateInfo instance_create_info(
    const VkApplicationInfo* app_info, 
    const VkDebugUtilsMessengerCreateInfoEXT* debug_info, 
    const std::vector<const char*>& exts
) 
{
    Utils::Logger::get()->info("Creating the Instance Info...");
    VkInstanceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pNext = nullptr;
    create_info.pApplicationInfo = app_info;
    create_info.enabledExtensionCount = static_cast<uint32_t>(exts.size());
    create_info.ppEnabledExtensionNames = reinterpret_cast<const char* const*>(exts.data());
    
    Utils::Logger::get()->info("Checking Valiation Layers Support...");
    if(Utils::checkValidationLayerSupport()) {
        Utils::Logger::get()->success("Validation layers is support!");
        create_info.enabledLayerCount = static_cast<uint32_t>(Utils::validationLayers.size());
        create_info.ppEnabledLayerNames = Utils::validationLayers.data();
        create_info.pNext = debug_info;
    }
    else  {
        Utils::Logger::get()->error("Validation Layers doesn't support!");
        create_info.enabledLayerCount = 0;
        create_info.ppEnabledLayerNames = nullptr;
    }
    
    Utils::Logger::get()->success("The Instance info was created!");
    return create_info;
}

void instance_create(Instance* instance) {
    Utils::Logger::get()->info("Creating an Instance...");
    VkApplicationInfo app_info = instance_create_app_info();
    VkDebugUtilsMessengerCreateInfoEXT debug_info = Utils::createDebugMessengerInfo();
    std::vector<const char*> exts = instance_get_required_exts();
    VkInstanceCreateInfo instance_info = instance_create_info(&app_info, &debug_info, exts);
    VkResult res = vkCreateInstance(&instance_info, nullptr, &instance->handle);
    if(res != VK_SUCCESS)
        Engine::Utils::Logger::get()->critical("The Instance creation Failed::" + std::to_string(res));
    Utils::Logger::get()->success("The Instance was Created!");
}

void instance_destroy(const Instance& instance) {
    Utils::Logger::get()->info("Destroying the Instance...");
    if(instance.handle == VK_NULL_HANDLE)
        Utils::Logger::get()->error("Cannot Destroy the Instance::Instance is not Created!");
    vkDestroyInstance(instance.handle, nullptr);
    Utils::Logger::get()->success("The Instance was Destroyed!");
}
