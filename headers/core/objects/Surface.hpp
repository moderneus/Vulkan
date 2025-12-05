#pragma once

#include "window/Window.hpp"

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
            void create(const Window::Window& window);
            void destroy();

            VkSurfaceKHR get() const;
        };
    }
}
