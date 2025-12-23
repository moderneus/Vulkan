#include <vulkan/vulkan.h>

struct Queue {
    VkQueue graphics = VK_NULL_HANDLE;
    VkQueue present = VK_NULL_HANDLE;
};
