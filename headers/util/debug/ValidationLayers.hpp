#pragma once

#include <vulkan/vulkan.h>

#include <vector>

namespace Engine
{
    namespace Utils
    {
        class ValidationLayers
        {
        private: 
            static const std::vector<const char*> validationLayers;
            bool debugging = false;
            
            VkDebugUtilsMessengerCreateInfoEXT createMessengerInfo();
            void createMessenger();

        public:
            static VKAPI_ATTR VkBool32 VKAPI_CALL messengerCallback
            (
                VkDebugUtilsMessageSeverityFlagBitsEXT messageSevetiry,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData
            );

            static const std::vector<const char*>& get();
            void enable();
            bool enabled();
            bool checkSupport();
        };
    }
}
