#pragma once

#include "core/vulkan/objects/device/QueueFamily.hpp"
#include "core/vulkan/objects/device/Queue.hpp"
#include "core/vulkan/objects/device/PhysicalDevice.hpp"

#include <vulkan/vulkan.h>

struct LogicalDevice {
    VkDevice handle = VK_NULL_HANDLE;
};

VkDeviceQueueCreateInfo device_create_queue_info(const QueueFamily& queue_family);

VkDeviceCreateInfo device_create_info(const PhysicalDevice& phys_device, const VkDeviceQueueCreateInfo& queue_info, VkPhysicalDeviceFeatures* phys_device_features);

void device_create(LogicalDevice* device, Queue* queue, const QueueFamily& queue_family, const PhysicalDevice& phys_device);

void device_destroy(const LogicalDevice& device);
