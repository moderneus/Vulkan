#pragma once

#include "core/objects/Instance.hpp"
#include "core/objects/PhysicalDevice.hpp"

#include <vulkan/vulkan.h>

namespace Engine
{
    namespace Core
    {
        class Core
        {
        private:    
            static Instance vkInstance;
            static PhysicalDevice vkPhysicalDevice;
            
        public: 
            void init();
            void destroy();
            
            static VkInstance getInstance();
            static VkPhysicalDevice getPhysicalDevice();
        };
    }
}
