#pragma once

#include <vulkan/vulkan.h>

namespace Engine
{
    namespace Core
    {
        class Surface 
        {
        private:
            VkSurfaceKHR surface = VK_NULL_HANDLE;

        public:
            void create();
            void destroy();

            VkSurfaceKHR get() const;
        };
    }
}
