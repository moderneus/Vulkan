#pragma once

#include "core/objects/LogicalDevice.hpp"

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

namespace Engine
{
    namespace Core
    {
        class ShaderModule 
        {
        private:
            VkShaderModule shaderModule = VK_NULL_HANDLE;

            VkShaderModuleCreateInfo createInfo(const std::vector<char>& src);

        public:
            void create(const LogicalDevice& device, const std::string& path);
            void destroy(const LogicalDevice& device);

            VkShaderModule get() const;
        };
    }
}
