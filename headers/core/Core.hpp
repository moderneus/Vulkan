#pragma once

#include "core/objects/Instance.hpp"

#include <vulkan/vulkan.h>

namespace Engine
{
    namespace Core
    {
        class Core
        {
        private:    
            static Instance vkInstance;
            
        public: 
            void init();
            void destroy();
            static VkInstance getInstance();
        };
    }
}
