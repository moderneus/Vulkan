#ifndef MOD_DEVICE_HPP
#define MOD_DEVICE_HPP

#include <vulkan/vulkan.h>

#include <vector>

struct physical_device;
struct queue_indices;
struct queue;

struct device
{
	VkDevice handle = VK_NULL_HANDLE;
};

VkPhysicalDeviceFeatures device_get_enabled_features(const physical_device &gpu);

std::vector<VkDeviceQueueCreateInfo> device_create_queue_infos(const queue_indices &q_idx, const float &prior);

VkDeviceQueueCreateInfo device_create_queue_info(const uint32_t q_idx, const float &prior);

VkDeviceCreateInfo device_create_info(const std::vector<VkDeviceQueueCreateInfo> &info, const VkPhysicalDeviceFeatures &features);

void device_create(device *dev, queue *q, const queue_indices &q_idx, const physical_device &gpu);

void device_destroy(const device &dev);

#endif
