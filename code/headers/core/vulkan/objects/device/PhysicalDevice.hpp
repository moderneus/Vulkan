#ifndef MOD_PHYSICAL_DEVICE_HPP
#define MOD_PHYSICAL_DEVICE_HPP

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

struct surface_t;
struct instance_t;

struct phys_device_t
{
	VkPhysicalDevice handle = VK_NULL_HANDLE;
};

const std::vector<const char*> phys_device_exts = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

uint32_t phys_device_rate(const phys_device_t& phys_device);

std::string phys_device_get_name(const phys_device_t& phys_device);

bool phys_device_check_ext_support(const phys_device_t& phys_device);

bool phys_device_is_suitable(const phys_device_t& phys_device, const surface_t& surface);

void phys_device_pick(phys_device_t* phys_device, const instance_t& instance, const surface_t& surface);

VkPhysicalDeviceFeatures phys_device_get_features(const phys_device_t& phys_device);

#endif
