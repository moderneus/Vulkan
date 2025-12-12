#pragma once

#include "core/objects/LogicalDevice.hpp"

#include <vulkan/vulkan.h>

namespace Engine
{
    namespace Core
    {
        class PipelineLayout
        {
        private:
            VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;

            VkPipelineLayoutCreateInfo createInfo();
            
        public:
            void create(const LogicalDevice& device);
            void destroy(const LogicalDevice& device);

            VkPipelineLayout get() const;
        };
    }
}
