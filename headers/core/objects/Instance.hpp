#pragma once

#include <vulkan/vulkan.h>

namespace Engine
{
    namespace Core
    {
        class Instance
        {
        private: 
            VkInstance instance = VK_NULL_HANDLE;

            VkApplicationInfo createAppInfo();
            VkInstanceCreateInfo createInstanceInfo(const VkApplicationInfo* appInfo);

        public: 
            void create();
            void destroy();
            
            VkInstance& get();
        };
    }
}
