#ifndef MOD_PHYS_DEV_HPP
#define MOD_PHYS_DEV_HPP

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

struct surface_t;
struct instance_t;

struct phys_device_t
{
	VkPhysicalDevice handle = VK_NULL_HANDLE;
};

const std::vector<const char*> phys_dev_exts = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

uint32_t phys_dev_rate(const phys_device_t &phys_dev);

std::string phys_dev_get_name(const phys_device_t &phys_dev);

bool phys_dev_check_ext_support(const phys_device_t &phys_dev);

bool phys_dev_is_suitable(const phys_device_t &phys_dev, const surface_t &surface);

void phys_dev_pick(phys_device_t *phys_dev, const instance_t &instance, const surface_t &surface);

VkPhysicalDeviceFeatures phys_dev_get_features(const phys_device_t &phys_dev);

uint32_t phys_dev_find_mem_type(const phys_device_t &phys_dev, uint32_t type_filter, VkMemoryPropertyFlags props);

#endif
