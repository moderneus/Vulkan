#include "util/debug/ValidationLayers.hpp"
#include "core/Core.hpp"

#include <vulkan/vulkan.h>
#include <fmt/core.h>
#include <fmt/color.h>

#include <cstring>
#include <vector>
#include <vulkan/vulkan_core.h>

const std::vector<const char*> Engine::Utils::ValidationLayers::validationLayers = {"VK_LAYER_KHRONOS_validation"};

VkDebugUtilsMessengerCreateInfoEXT Engine::Utils::ValidationLayers::createMessengerInfo()
{
    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;

    createInfo.pfnUserCallback = Engine::Utils::ValidationLayers::messengerCallback;
    createInfo.pUserData = nullptr;

    return createInfo;
}

VKAPI_ATTR VkBool32 VKAPI_CALL Engine::Utils::ValidationLayers::messengerCallback
(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSevetiry,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData
)
{
    fmt::color col;

    if(messageSevetiry & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
        col = fmt::color::red;

    else if(messageSevetiry & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
        col = fmt::color::gold;

    else
        col = fmt::color::white_smoke;
    
    fmt::print(fmt::fg(fmt::color::dark_red), "[VULKAN]");
    fmt::print(fmt::fg(col), "{}::", pCallbackData->pMessageIdName);
    fmt::print(fmt::fg(fmt::color::white), "{}\n", pCallbackData->pMessage);
    
    return VK_FALSE;
}

void Engine::Utils::ValidationLayers::createMessenger()
{
    VkDebugUtilsMessengerEXT messenger;
    VkDebugUtilsMessengerCreateInfoEXT createInfo = createMessengerInfo();
    vkCreateDebugUtilsMessengerEXT(Core::Core::getInstance(), &createInfo, nullptr, &messenger);
}

const std::vector<const char*>& Engine::Utils::ValidationLayers::get()
{
    return validationLayers;
}

void Engine::Utils::ValidationLayers::enable()
{
    debugging = true;
}

bool Engine::Utils::ValidationLayers::enabled()
{
    return debugging;
}

bool Engine::Utils::ValidationLayers::checkSupport()
{
    uint32_t layersCount;
    vkEnumerateInstanceLayerProperties(&layersCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layersCount);
    vkEnumerateInstanceLayerProperties(&layersCount, availableLayers.data());

    for(const char* layerName : validationLayers)
    {
        bool layerFound = false;

        for(const auto& layerProperties : availableLayers)
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
