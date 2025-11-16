#include "core/objects/Instance.hpp"

#include <SDL3/SDL_vulkan.h>
#include <fmt/core.h>

#include <cstdlib>

VkApplicationInfo Instance::createAppInfo()
{
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.apiVersion = VK_API_VERSION_1_4;

    return appInfo;
}

VkInstanceCreateInfo Instance::createInstanceInfo(VkApplicationInfo* appInfo)
{
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = appInfo;

    uint32_t extensionsCount;
    const char* const* extensions;
    
    extensions = SDL_Vulkan_GetInstanceExtensions(&extensionsCount);
    
    createInfo.enabledExtensionCount = extensionsCount;
    createInfo.ppEnabledExtensionNames = extensions;
    createInfo.enabledLayerCount = 0;

    return createInfo;
}

void Instance::create()
{
    VkApplicationInfo appInfo = createAppInfo();
    VkInstanceCreateInfo createInfo = createInstanceInfo(&appInfo);

    if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
        std::exit(-1);

    fmt::print("Instance created!\n");
}

void Instance::destroy()
{
    vkDestroyInstance(instance, nullptr);
}

VkInstance& Instance::get()
{
    return instance;
}
