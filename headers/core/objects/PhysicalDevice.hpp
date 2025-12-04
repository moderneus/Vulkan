#pragma once

#include <string>
#include <vulkan/vulkan.h>

namespace Engine
{
    namespace Core
    {
        class PhysicalDevice
        {
        private:
            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

            int rate(const VkPhysicalDevice& device);
            std::string name(const VkPhysicalDevice& device);
            bool isSuitable(const VkPhysicalDevice& device);

        public:
            void pick();

            VkPhysicalDevice get();
        };
    }
}

