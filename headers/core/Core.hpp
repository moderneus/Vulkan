#pragma once

#include "core/objects/Instance.hpp"
#include "core/objects/PhysicalDevice.hpp"
#include "core/objects/LogicalDevice.hpp"
#include "core/objects/Surface.hpp"
#include "core/objects/Swapchain.hpp"
#include "core/objects/ImageView.hpp"
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
            Swapchain vkSwapchain;
            ImageView vkImageView;
            
        public: 
            void init();
            void destroy();
            
            VkInstance getInstance();
            VkPhysicalDevice getPhysicalDevice();
        };
    }
}
