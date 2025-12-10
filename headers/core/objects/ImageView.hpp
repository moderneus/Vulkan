#pragma once

#include "core/objects/LogicalDevice.hpp"

#include <vulkan/vulkan.h>

#include <vector>

namespace Engine
{
    namespace Core
    {
        class ImageView
        {
        private:
            VkImageView imageView = VK_NULL_HANDLE;
            
            std::vector<VkImageView> imageViews;  
            std::vector<VkImage> images;
            VkFormat imageFormat;

            VkImageViewCreateInfo createInfo();

        public:
            void create(const LogicalDevice& device);
            void destroy(const LogicalDevice& device);

            VkImageView get() const;
        };
    }
}
