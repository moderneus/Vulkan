#include "util/debug/ValidationLayers.hpp"
#include "util/debug/Logger.hpp"
#include "core/Core.hpp"

#include "fmt/core.h"
#include "fmt/color.h"

#include <vulkan/vulkan.h>

#include <vector>
#include <cstring>
#include <cstdint>

bool Engine::Utils::checkValidationLayerSupport()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for(const char* layerName: validationLayers)
    {
        bool layerFound = false;

        for(const auto& layerProperties: availableLayers)
        {
            if(strcmp(layerName, layerProperties.layerName) == 0)
            {
                layerFound = true;
                break;
            }
        }

        if(!layerFound)
            return false;
    }

    return true;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL Engine::Utils::callBack
(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallBackData,
    void* pUserData
)
{
    fmt::print(fmt::fg(fmt::color::dark_red), "[VULKAN] ");

    fmt::color color;

    switch(messageSeverity)
    {
        default:
            color = fmt::color::white;
        break;
        
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            color = fmt::color::lime_green;
        break;

        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            color = fmt::color::gold;
        break;

        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            color = fmt::color::red;
        break;
    }

    fmt::print(fmt::fg(color), "{}: ", pCallBackData->pMessageIdName);
    fmt::print(fmt::fg(fmt::color::white), "{}\n", pCallBackData->pMessage);

    return VK_FALSE;
}

VkDebugUtilsMessengerCreateInfoEXT Engine::Utils::createDebugMessengerInfo()
{
    Utils::Logger::get()->info("Creating a Debug Messenger Info...");

    VkDebugUtilsMessengerCreateInfoEXT createInfo {};

    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
                                 
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
    createInfo.pfnUserCallback = Engine::Utils::callBack;
    createInfo.pUserData = nullptr;

    Utils::Logger::get()->success("The Debug Messenger Info was created!");

    return createInfo;
}

void Engine::Utils::setupDebugMessenger()
{
    Utils::Logger::get()->info("Creating a Debug Messenger...");

    VkDebugUtilsMessengerCreateInfoEXT createInfo = createDebugMessengerInfo();
    VkDebugUtilsMessengerEXT debugMessenger;
    
    if(createDebugMessenger(Engine::Core::Core::getInstance(), &createInfo, nullptr, &debugMessenger) != VK_SUCCESS)
        Utils::Logger::get()->error("Failed to Create the Debug Messenger!");

    else
        Utils::Logger::get()->success("The Debug Messenger was Created!");
}

VkResult Engine::Utils::createDebugMessenger
(
    VkInstance instance, 
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
    const VkAllocationCallbacks* pAllocator, 
    VkDebugUtilsMessengerEXT* pDebugMessenger
)
{    
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(Engine::Core::Core::getInstance(), "vkCreateDebugUtilsMessengerEXT");

    if(func != nullptr)
        func(Engine::Core::Core::getInstance(), pCreateInfo, pAllocator, pDebugMessenger);

    else
        return VK_ERROR_EXTENSION_NOT_PRESENT;

    return VK_SUCCESS;
}
