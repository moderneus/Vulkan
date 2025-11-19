#include "core/objects/Instance.hpp"
#include "util/String.hpp"
#include "util/debug/ValidationLayers.hpp"
#include "util/debug/Logger.hpp"

#include <SDL3/SDL_vulkan.h>

VkApplicationInfo Engine::Core::Instance::createAppInfo()
{
    Utils::Logger::get()->info("Creating an Application Info...");
    
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 2);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 2);
    appInfo.apiVersion = VK_API_VERSION_1_4;

    Utils::Logger::get()->success("The Application Info created!");

    return appInfo;
}

VkInstanceCreateInfo Engine::Core::Instance::createInstanceInfo(const VkApplicationInfo* appInfo)
{
    Utils::Logger::get()->info("Creating the Instance Info...");
    
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = appInfo;

    uint32_t extensionsCount;
    const char* const* extensions;
    
    extensions = SDL_Vulkan_GetInstanceExtensions(&extensionsCount);

    std::vector<std::string> extensionNames = Utils::cstrArrayToStringVector(extensions, extensionsCount);

    Utils::Logger::get()->info("Extensions = ", extensionNames);
    Utils::Logger::get()->info("Extensions count = " + std::to_string(extensionsCount));
    
    createInfo.enabledExtensionCount = extensionsCount;
    createInfo.ppEnabledExtensionNames = extensions;

    Utils::ValidationLayers validationLayers;

#ifdef DEBUG
    validationLayers.enable();
#endif
    
    if(validationLayers.enabled() && validationLayers.checkSupport())
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.get().size());
        createInfo.ppEnabledLayerNames = Utils::ValidationLayers::get().data();
    }

    else
    {
        createInfo.enabledLayerCount = 0;
    }

    Utils::Logger::get()->success("The Instance info was created!");

    return createInfo;
}

void Engine::Core::Instance::create()
{
    Utils::Logger::get()->info("Creating an Instance...");

    VkApplicationInfo appInfo = createAppInfo();
    VkInstanceCreateInfo createInfo = createInstanceInfo(&appInfo);

    VkResult res = vkCreateInstance(&createInfo, nullptr, &instance);
        
    if(res != VK_SUCCESS)
        Engine::Utils::Logger::get()->critical("The Instance creation Failed::" + std::to_string(res));

    Utils::Logger::get()->success("The Instance was Created!");
}

void Engine::Core::Instance::destroy()
{
    Utils::Logger::get()->info("Destroying the Instance...");
   
    if(instance == VK_NULL_HANDLE)
        Utils::Logger::get()->critical("Cannot Destroy the Instance::Instance is not Created!");
        
    vkDestroyInstance(instance, nullptr);
    
    Utils::Logger::get()->success("The Instance was Destroyed!");
}

VkInstance Engine::Core::Instance::get()
{
    return instance;
}
