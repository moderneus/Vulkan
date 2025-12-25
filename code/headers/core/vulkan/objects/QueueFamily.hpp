#pragma once

#include "core/vulkan/objects/PhysicalDevice.hpp"
#include "core/vulkan/objects/Surface.hpp"

#include <vulkan/vulkan.h>

#include <cstdint>
#include <optional>

struct QueueFamily {
    std::optional<uint32_t> graphics;
    std::optional<uint32_t> present;
};

bool queue_family_is_complete();

void queue_family_find(QueueFamily* queue_family, const PhysicalDevice& phys_device, const Surface& surface);
