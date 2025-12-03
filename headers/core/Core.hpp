#pragma once

#include "core/objects/Instance.hpp"
#include "core/objects/PhysicalDevice.hpp"

#include "util/Singleton.hpp"

#include <vulkan/vulkan.h>

namespace Engine
{
    namespace Core
    {
        class Core : public Utils::Singleton<Core>
        {
        private:    
            Instance vkInstance;
            PhysicalDevice vkPhysicalDevice;
            
        public: 
            void init();
            void destroy();
            
            VkInstance getInstance();
            VkPhysicalDevice getPhysicalDevice();
        };
    }
}
