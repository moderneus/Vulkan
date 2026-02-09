#ifndef MOD_DEV_HPP
#define MOD_DEV_HPP

#include <vulkan/vulkan.h>

#include <vector>

struct phys_device_t;
struct queue_family_t;
struct queue_t;

struct device_t
{
	VkDevice handle = VK_NULL_HANDLE;
};

VkPhysicalDeviceFeatures dev_get_enabled_features(const phys_device_t &phys_dev);

std::vector<VkDeviceQueueCreateInfo> dev_create_queue_infos(const queue_family_t &qf, const float &prior);

VkDeviceQueueCreateInfo dev_create_queue_info(const uint32_t qf_idx, const float &prior);

VkDeviceCreateInfo dev_create_info(const std::vector<VkDeviceQueueCreateInfo> &info, const VkPhysicalDeviceFeatures &features);

void dev_create(device_t *dev, queue_t *q, const queue_family_t &qf, const phys_device_t &phys_dev);

void dev_destroy(const device_t &dev);

#endif
