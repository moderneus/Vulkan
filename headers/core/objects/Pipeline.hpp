#pragma once

#include "core/objects/LogicalDevice.hpp"
#include "core/objects/ShaderModule.hpp"

#include <array>
#include <vulkan/vulkan.h>

namespace Engine
{
    namespace Core
    {
        class Pipeline
        {
        private:
            VkPipeline pipeline = VK_NULL_HANDLE;
 
            struct PipelineState
            {
                std::array<VkPipelineShaderStageCreateInfo, 2> shaderStages = {};
                VkPipelineDynamicStateCreateInfo dynamicStateInfo = {};
                VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
                VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo = {};
                VkPipelineViewportStateCreateInfo viewportInfo = {};
                VkPipelineRasterizationStateCreateInfo rasterizationInfo = {};
                VkPipelineMultisampleStateCreateInfo multisampleInfo = {};
                VkPipelineDepthStencilStateCreateInfo depthStencilInfo = {};
                VkPipelineColorBlendStateCreateInfo colorBlendInfo = {};
            };
            
            std::array<ShaderModule, 2> createShaderModules();
            std::array<VkPipelineShaderStageCreateInfo, 2> createShaderStageInfo(const std::array<ShaderModule, 2>& shaderModules);
            VkPipelineDynamicStateCreateInfo createDynamicStateInfo();
            VkPipelineVertexInputStateCreateInfo createVertexInputInfo();
            VkPipelineInputAssemblyStateCreateInfo createInputAssemblyInfo();
            VkPipelineViewportStateCreateInfo createViewportInfo();
            VkPipelineRasterizationStateCreateInfo createRasterizationInfo();
            VkPipelineMultisampleStateCreateInfo createMultisampleInfo();
            VkPipelineDepthStencilStateCreateInfo createDepthStencilInfo();
            VkPipelineColorBlendStateCreateInfo createColorBlendInfo();

        public:
            void create(const LogicalDevice& device);
            void destroy(const LogicalDevice& device);

            VkPipeline get() const;
        };
    }
}
