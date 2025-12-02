#pragma once

#include <vulkan/vulkan.h>

#include <vector>

namespace Engine
{
    namespace Core
    {
        class Instance
        {
        private: 
            VkInstance instance = VK_NULL_HANDLE;

            VkApplicationInfo createAppInfo();
            VkInstanceCreateInfo createInstanceInfo(const VkApplicationInfo* appInfo, VkDebugUtilsMessengerCreateInfoEXT* debugInfo);
            std::vector<const char*> getRequiredExtensions();

        public: 
            void create();
            void destroy();
            
            VkInstance get();
        };
    }
}
