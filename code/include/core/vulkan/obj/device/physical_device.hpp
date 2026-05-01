#ifndef MOD_PHYSICAL_DEVICE_HPP
#define MOD_PHYSICAL_DEVICE_HPP

#include <vulkan/vulkan.h>

#include <string>
#include <vector>

struct surface;
struct instance;

struct physical_device {
	VkPhysicalDevice handle = VK_NULL_HANDLE;
};

const std::vector<const char*> physical_device_exts = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

uint32_t physical_device_rate(const physical_device &gpu);

std::string physical_device_get_name(const physical_device &gpu);

bool physical_device_check_ext_supp(const physical_device &gpu);

bool physical_device_is_suitable(const physical_device &gpu, const surface &surf);

void physical_device_pick(physical_device *gpu, const instance &inst, const surface &surf);

VkPhysicalDeviceFeatures physical_device_get_features(const physical_device &gpu);

uint32_t physical_device_find_mem_type(const physical_device &gpu, uint32_t type_filter, VkMemoryPropertyFlags props);

VkFormat physical_device_find_supp_fmt(const physical_device &gpu, const std::vector<VkFormat> &fmts, VkImageTiling tiling, VkFormatFeatureFlags features);

VkSampleCountFlagBits physical_device_get_max_usable_sample_cnt(const physical_device &gpu);

#endif
