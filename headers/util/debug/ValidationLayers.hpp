#pragma once

#include <vulkan/vulkan.h>

#include <vector>
#include <vulkan/vulkan_core.h>

namespace Engine
{
    namespace Utils
    {
        const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
        VkDebugUtilsMessengerEXT debugMessenger;

        bool checkValidationLayerSupport();

        static VKAPI_ATTR VkBool32 VKAPI_CALL callBack
        (
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallBackData,
            void* pUserData
        );

        VkDebugUtilsMessengerCreateInfoEXT createDebugMessengerInfo();

        void setupDebugMessenger();

        VkResult createDebugMessenger
        (
            VkInstance instance, 
            const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
            const VkAllocationCallbacks* pAllocator, 
            VkDebugUtilsMessengerEXT* pDebugMessenger
        );
    }
}