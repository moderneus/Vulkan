#pragma once

#include <vulkan/vulkan.h>

#include <cstdint>
#include <optional>

struct QueueFamily {
    std::optional<uint32_t> graphics;
    std::optional<uint32_t> present;
};

bool queue_family_is_complete();
QueueFamily queue_family_find(const VkPhysicalDevice& phys_device, const VkSurfaceKHR& surface);
