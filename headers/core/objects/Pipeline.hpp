#pragma once

#include "core/objects/LogicalDevice.hpp"
#include "core/objects/ShaderModule.hpp"

#include <vulkan/vulkan.h>

#include <array>

namespace Engine
{
    namespace Core
    {
        class Pipeline
        {
        private:
            VkPipeline pipeline = VK_NULL_HANDLE;

            ShaderModule vertShaderModule;
            ShaderModule fragShaderModule;

            std::array<VkPipelineShaderStageCreateInfo, 2> createShaderStageInfo();

        public:
            void create(const LogicalDevice& device);
            void destroy(const LogicalDevice& device);

            VkPipeline get() const;
        };
    }
}
