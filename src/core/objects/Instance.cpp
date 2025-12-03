#include "core/objects/Instance.hpp"
#include "util/String.hpp"
#include "util/debug/ValidationLayers.hpp"
#include "util/debug/Logger.hpp"

#include "SDL3/SDL_vulkan.h"

#include <vulkan/vulkan.h>

#include <cstdint>

std::vector<const char*> Engine::Core::Instance::getRequiredExtensions()
{
    uint32_t extensionsCount = 0;
    const char* const* extensions;
    
    extensions = SDL_Vulkan_GetInstanceExtensions(&extensionsCount);

    std::vector<const char*> extensionsVector(extensions, extensions + extensionsCount);

    extensionsVector.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    Utils::Logger::get()->info("Extensions = ", Utils::cstrVectorToStringVector(extensionsVector));
    Utils::Logger::get()->info("Extensions count = " + std::to_string(extensionsCount));

    return extensionsVector;
}

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

VkInstanceCreateInfo Engine::Core::Instance::createInstanceInfo(const VkApplicationInfo* appInfo, const VkDebugUtilsMessengerCreateInfoEXT* debugInfo, const std::vector<const char*>& extensions)
{
    Utils::Logger::get()->info("Creating the Instance Info...");
    
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pNext = nullptr;
    createInfo.pApplicationInfo = appInfo;
    
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = (const char* const*)extensions.data();

    Utils::Logger::get()->info("Checking Valiation Layers Support...");
    
    if(Utils::checkValidationLayerSupport())
    {
        Utils::Logger::get()->success("Validation layers is support!");

        createInfo.enabledLayerCount = static_cast<uint32_t>(Utils::validationLayers.size());
        createInfo.ppEnabledLayerNames = Utils::validationLayers.data();
        createInfo.pNext = debugInfo;
    }
    
    else 
    {
        Utils::Logger::get()->error("Validation Layers doesn't support!");

        createInfo.enabledLayerCount = 0;
        createInfo.ppEnabledLayerNames = nullptr;
    }
    
    Utils::Logger::get()->success("The Instance info was created!");

    return createInfo;
}

void Engine::Core::Instance::create()
{
    Utils::Logger::get()->info("Creating an Instance...");

    VkApplicationInfo appInfo = createAppInfo();
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = Utils::createDebugMessengerInfo();
    std::vector<const char*> extensions = getRequiredExtensions();

    VkInstanceCreateInfo createInfo = createInstanceInfo(&appInfo, &debugCreateInfo, extensions);

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
