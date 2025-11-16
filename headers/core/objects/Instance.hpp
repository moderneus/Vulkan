#pragma once

#include <vulkan/vulkan.h>

namespace Engine
{
    namespace Core
    {
        class Instance
        {
        private: 
            VkInstance instance;

            VkApplicationInfo createAppInfo();
            VkInstanceCreateInfo createInstanceInfo(VkApplicationInfo* appInfo);

        public: 
            void create();
            void destroy();
            
            VkInstance& get();
        };
    }
}
