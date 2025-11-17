#include "core/objects/Instance.hpp"
#include "util/String.hpp"
#include "util/Logger.hpp"

#include <SDL3/SDL_vulkan.h>

VkApplicationInfo Engine::Core::Instance::createAppInfo()
{
    Engine::Utils::log->info("Creating an Application Info...");
    
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.apiVersion = VK_API_VERSION_1_4;

    Engine::Utils::log->success("The Application Info created!");

    return appInfo;
}

VkInstanceCreateInfo Engine::Core::Instance::createInstanceInfo(const VkApplicationInfo* appInfo)
{
    Engine::Utils::log->info("Creating the Instance Info...");
    
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = appInfo;

    uint32_t extensionsCount;
    const char* const* extensions;
    
    extensions = SDL_Vulkan_GetInstanceExtensions(&extensionsCount);

    std::vector<std::string> extensionNames = cstrArrayToVector(extensions, extensionsCount);

    Engine::Utils::log->info("Extensions = ", extensionNames);
    Engine::Utils::log->info("Extensions count = " + std::to_string(extensionsCount));
    
    createInfo.enabledExtensionCount = extensionsCount;
    createInfo.ppEnabledExtensionNames = extensions;
    createInfo.enabledLayerCount = 0;

    Engine::Utils::log->success("The Instance info was created!");

    return createInfo;
}

void Engine::Core::Instance::create()
{
    Engine::Utils::log->info("Creating an Instance...");

    VkApplicationInfo appInfo = createAppInfo();
    VkInstanceCreateInfo createInfo = createInstanceInfo(&appInfo);

    VkResult res = vkCreateInstance(&createInfo, nullptr, &instance);
        
    if(res != VK_SUCCESS)
        Engine::Utils::log->critical("The Instance creation Failed::" + std::to_string(res));

    Engine::Utils::log->success("The Instance was Created!");
}

void Engine::Core::Instance::destroy()
{
    Engine::Utils::log->info("Destroying the Instance...");
   
    if(instance == VK_NULL_HANDLE)
        Engine::Utils::log->critical("Cannot Destroy the Instance::Instance is not Created!");
        
    vkDestroyInstance(instance, nullptr);
    
    Engine::Utils::log->success("The Instance was Destroyed!");
}

VkInstance Engine::Core::Instance::get()
{
    return instance;
}
