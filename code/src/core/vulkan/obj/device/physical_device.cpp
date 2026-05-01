#include "core/vulkan/obj/device/physical_device.hpp"
#include "core/vulkan/obj/instance/instance.hpp"
#include "core/vulkan/obj/instance/surface.hpp"
#include "core/vulkan/obj/swapchain/swapchain.hpp"
#include "util/debug/log.hpp"

#include <vulkan/vulkan.h>

#include <string>
#include <vector>
#include <map>
#include <set>

std::string physical_device_get_name(const VkPhysicalDevice &gpu)
{
	VkPhysicalDeviceProperties props;
	vkGetPhysicalDeviceProperties(gpu, &props);
	return props.deviceName;
}

uint32_t physical_device_rate(const VkPhysicalDevice &gpu) 
{
	log_info("Rating the Physical Device with Name: ", physical_device_get_name(gpu));

	VkPhysicalDeviceProperties props;
	vkGetPhysicalDeviceProperties(gpu, &props);

	uint32_t scr = 0;

	if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		scr += 1000;

	scr += props.limits.maxImageDimension2D;

	log_info("The Score of Physical Device is: ", std::to_string(scr));

	return scr;
}

bool physical_device_check_ext_supp(const VkPhysicalDevice &gpu)
{
	log_info("Checking the Physical Device Supported Extensions...");

	uint32_t ext_cnt;
	vkEnumerateDeviceExtensionProperties(gpu, nullptr, &ext_cnt, nullptr);

	std::vector<VkExtensionProperties> exts(ext_cnt);
	vkEnumerateDeviceExtensionProperties(gpu, nullptr, &ext_cnt, exts.data());

	std::set<std::string> req_exts(physical_device_exts.begin(), physical_device_exts.end());

	for(const auto &ext : exts)
		req_exts.erase(ext.extensionName);

	if(!req_exts.empty())
		log_critical("The Physical Device doesn't Support the Required Extensions.");

	log_info("The Physical Device Supports the Required Extensions.");

	return req_exts.empty();
}

bool physical_device_is_suitable(const VkPhysicalDevice &gpu, const surface &surf)
{
	return physical_device_check_ext_supp(gpu) && swapchain_is_adequate(gpu, surf.handle);
}

void physical_device_pick(physical_device *gpu, const instance &inst, const surface &surf)
{
	log_info("Searching a Suitable GPU...");

	uint32_t gpu_cnt = 0;
	vkEnumeratePhysicalDevices(inst.handle, &gpu_cnt, nullptr);

	if (!gpu_cnt)
		log_critical("Failed to find GPU with Vulkan support.");

	std::vector<VkPhysicalDevice> gpus(gpu_cnt);
	vkEnumeratePhysicalDevices(inst.handle, &gpu_cnt, gpus.data());

	std::multimap<uint32_t, VkPhysicalDevice> best;

	for(const VkPhysicalDevice &gpu : gpus) {
		if (physical_device_is_suitable(gpu, surf)) {
			uint32_t scr = physical_device_rate(gpu);
			best.insert(std::make_pair(scr, gpu));
		}
	}

	if (!best.empty() && best.rbegin()->first > 0)
		gpu->handle = best.rbegin()->second;
	else
		log_critical("Failed to Find any Suitable GPU.");
	

	log_info("The Suitable GPU was Found: ", physical_device_get_name(gpu->handle));
}

VkPhysicalDeviceFeatures physical_device_get_features(const physical_device &gpu) 
{
	log_info("Getting the Physical Device Features...");

	VkPhysicalDeviceFeatures features = {};
	vkGetPhysicalDeviceFeatures(gpu.handle, &features);

	if (features.samplerAnisotropy != VK_TRUE)
		log_critical("The found GPU doesn't have a Anistropy Filtrening Support.");

	log_info("The Physical Device Features were Got");

	return features;
}

uint32_t physical_device_find_mem_type(const physical_device &gpu, uint32_t type_filter, VkMemoryPropertyFlags props)
{
	log_info("Searching the Physical Device Memory Type...");

	VkPhysicalDeviceMemoryProperties mem_props = {};
	vkGetPhysicalDeviceMemoryProperties(gpu.handle, &mem_props);

	for(uint32_t i = 0; i < mem_props.memoryTypeCount; ++i) {
		if ((type_filter & (1 << i)) && (mem_props.memoryTypes[i].propertyFlags & props) == props)
			return i;
	}

	log_info("The Physical Device Memory Type was Found.");
	
	return -1;
}

VkFormat physical_device_find_supp_fmt(const physical_device &gpu, const std::vector<VkFormat> &fmts, VkImageTiling tiling, VkFormatFeatureFlags features)
{
	log_info("Searching the Physical Device Supported Format...");

	for(VkFormat fmt : fmts) {
		VkFormatProperties props;
		vkGetPhysicalDeviceFormatProperties(gpu.handle, fmt, &props);

		if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
			log_info("The Physical Device Supported Format Was Found.");
			return fmt;
		}
		else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
			log_info("The Physical Device Supported Format was Found.");
			return fmt;
		}
	}

	log_critical("Failed to Find Supported Format.");

	return VK_FORMAT_UNDEFINED;
}

VkSampleCountFlagBits physical_device_get_max_usable_sample_cnt(const physical_device &gpu) 
{
	log_info("Getting the Physical Device Max Usable Samples...");

	VkPhysicalDeviceProperties props;
	vkGetPhysicalDeviceProperties(gpu.handle, &props);

	VkSampleCountFlags cnts = props.limits.framebufferColorSampleCounts & props.limits.framebufferDepthSampleCounts;

	if (cnts & VK_SAMPLE_COUNT_64_BIT) {
		log_info("The Physical Device Max Usable Samples were Got.");
		return VK_SAMPLE_COUNT_64_BIT;
	}
	if (cnts & VK_SAMPLE_COUNT_32_BIT) {
		log_info("The Physical Device Max Usable Samples were Got.");
		return VK_SAMPLE_COUNT_32_BIT;
	}
	if (cnts & VK_SAMPLE_COUNT_16_BIT) {
		log_info("The Physical Device Max Usable Samples were Got.");
		return VK_SAMPLE_COUNT_16_BIT;
	}
	if (cnts & VK_SAMPLE_COUNT_8_BIT) {
		log_info("The Physical Device Max Usable Samples were Got.");
		return VK_SAMPLE_COUNT_8_BIT;
	}
	if (cnts & VK_SAMPLE_COUNT_4_BIT) {
		log_info("The Physical Device Max Usable Samples were Got.");
		return VK_SAMPLE_COUNT_4_BIT;
	}
	if (cnts & VK_SAMPLE_COUNT_4_BIT) {
		log_info("The Physical Device Max Usable Samples were Got.");
		return VK_SAMPLE_COUNT_2_BIT;
	}
		
	log_info("The Physical Device Max Usable Samples were Got.");

	return VK_SAMPLE_COUNT_1_BIT;
}
