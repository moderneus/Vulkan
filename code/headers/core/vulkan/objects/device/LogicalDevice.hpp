#pragma once

#include <vulkan/vulkan.h>

#include <vector>

struct PhysicalDevice;
struct QueueFamily;
struct Queue;

struct LogicalDevice {
    VkDevice handle = VK_NULL_HANDLE;
};

VkPhysicalDeviceFeatures device_get_enabled_features(const PhysicalDevice& phys_device);

std::vector<VkDeviceQueueCreateInfo> device_create_queue_infos(const QueueFamily& queue_family, const float& queue_priority);

VkDeviceQueueCreateInfo device_create_queue_info(const uint32_t queue_family_idx, const float& queue_priority);

VkDeviceCreateInfo device_create_info(const std::vector<VkDeviceQueueCreateInfo>& queue_info, const VkPhysicalDeviceFeatures& phys_device_features);

void device_create(LogicalDevice* device, Queue* queue, const QueueFamily& queue_family, const PhysicalDevice& phys_device);

void device_destroy(const LogicalDevice& device);
