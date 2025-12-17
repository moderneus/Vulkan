#pragma once

#include "core/vulkan/objects/PhysicalDevice.hpp"
#include "core/vulkan/objects/Surface.hpp"

#include <vulkan/vulkan.h>

struct LogicalDevice {
    VkDevice handle = VK_NULL_HANDLE;
};

VkDeviceQueueCreateInfo device_create_queue_info(const PhysicalDevice& phys_device, const Surface& surface);

VkDeviceCreateInfo device_create_info(
    PhysicalDevice& phys_device, 
    const VkDeviceQueueCreateInfo& queue_info, 
    VkPhysicalDeviceFeatures* phys_device_features
);

void device_create(LogicalDevice* device, PhysicalDevice& phys_device, const Surface& surface);

void device_destroy(const LogicalDevice& device);
