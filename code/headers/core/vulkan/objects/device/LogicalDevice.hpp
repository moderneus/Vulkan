#ifndef MOD_LOGICAL_DEVICE_HPP
#define MOD_LOGICAL_DEVICE_HPP

#include <vulkan/vulkan.h>

#include <vector>

struct phys_device_t;
struct queue_family_t;
struct queue_t;

struct device_t
{
	VkDevice handle = VK_NULL_HANDLE;
};

VkPhysicalDeviceFeatures device_get_enabled_features(const phys_device_t& phys_device);

std::vector<VkDeviceQueueCreateInfo> device_create_queue_infos(const queue_family_t& queue_family, const float& queue_priority);

VkDeviceQueueCreateInfo device_create_queue_info(const uint32_t queue_family_idx, const float& queue_priority);

VkDeviceCreateInfo device_create_info(const std::vector<VkDeviceQueueCreateInfo>& queue_info, const VkPhysicalDeviceFeatures& phys_device_features);

void device_create(device_t* device, queue_t* queue, const queue_family_t& queue_family, const phys_device_t& phys_device);

void device_destroy(const device_t& device);

#endif
