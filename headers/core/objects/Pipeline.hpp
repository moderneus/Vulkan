#pragma once

#include "core/objects/LogicalDevice.hpp"
#include "core/objects/ShaderModule.hpp"
#include "core/objects/Swapchain.hpp"

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

            ShaderModule vertexShader;
            ShaderModule fragmentShader;
 
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
            
            VkViewport createViewport(const Swapchain& swapchain);
            VkRect2D createScissor(const Swapchain& swapchain);
            void createShaderModules(const LogicalDevice& device);
            std::array<VkPipelineShaderStageCreateInfo, 2> createShaderStageInfo();
            VkPipelineDynamicStateCreateInfo createDynamicStateInfo();
            VkPipelineVertexInputStateCreateInfo createVertexInputInfo();
            VkPipelineInputAssemblyStateCreateInfo createInputAssemblyInfo();
            VkPipelineViewportStateCreateInfo createViewportInfo(const VkViewport& viewport, const VkRect2D& scissor);
            VkPipelineRasterizationStateCreateInfo createRasterizationInfo();
            VkPipelineMultisampleStateCreateInfo createMultisampleInfo();
            VkPipelineDepthStencilStateCreateInfo createDepthStencilInfo();
            VkPipelineColorBlendStateCreateInfo createColorBlendInfo();

        public:
            void create(const LogicalDevice& device, const Swapchain& swapchain);
            void destroy(const LogicalDevice& device);

            VkPipeline get() const;
        };
    }
}
