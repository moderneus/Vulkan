#pragma once

#include "core/objects/Instance.hpp"
#include "core/objects/PhysicalDevice.hpp"
#include "core/objects/LogicalDevice.hpp"
#include "core/objects/Surface.hpp"
#include "window/Window.hpp"
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
            LogicalDevice vkLogicalDevice;
            Surface vkSurface;
            
        public: 
            void init(const Window::Window& window);
            void destroy();
            
            VkInstance getInstance();
            VkPhysicalDevice getPhysicalDevice();
        };
    }
}
