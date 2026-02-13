#include "core/vulkan/objects/device/PhysicalDevice.hpp"
#include "core/vulkan/objects/instance/Instance.hpp"
#include "core/vulkan/objects/instance/Surface.hpp"
#include "core/vulkan/objects/swapchain/Swapchain.hpp"
#include "util/debug/Logger.hpp"

#include <vulkan/vulkan.h>

#include <string>
#include <vector>
#include <map>
#include <set>

uint32_t phys_dev_rate(const VkPhysicalDevice &phys_dev) 
{
	VkPhysicalDeviceProperties props;
	vkGetPhysicalDeviceProperties(phys_dev, &props);

	uint32_t scr = 0;

	if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
		scr += 1000;
	}

	scr += props.limits.maxImageDimension2D;

	return scr;
}

std::string phys_dev_get_name(const phys_device_t &phys_dev)
{
	VkPhysicalDeviceProperties props;
	vkGetPhysicalDeviceProperties(phys_dev.handle, &props);
	return props.deviceName;
}

bool phys_dev_check_ext_supp(const VkPhysicalDevice &phys_dev)
{
	uint32_t ext_count;
	vkEnumerateDeviceExtensionProperties(phys_dev, nullptr, &ext_count, nullptr);

	std::vector<VkExtensionProperties> exts(ext_count);
	vkEnumerateDeviceExtensionProperties(phys_dev, nullptr, &ext_count, exts.data());

	std::set<std::string> req_exts(phys_dev_exts.begin(), phys_dev_exts.end());

	for(const auto& ext : exts) {
		req_exts.erase(ext.extensionName);
	}

	return req_exts.empty();
}

bool phys_dev_is_suitable(const VkPhysicalDevice &phys_dev, const surface_t &surf)
{
	return phys_dev_check_ext_supp(phys_dev) && swp_is_adequate(phys_dev, surf.handle);
}

void phys_dev_pick(phys_device_t *phys_dev, const instance_t &inst, const surface_t &surf)
{
	log_info("Searching a Suitable GPU...");

	uint32_t phys_dev_cnt = 0;
	vkEnumeratePhysicalDevices(inst.handle, &phys_dev_cnt, nullptr);

	if (phys_dev_cnt == 0) {
		log_critical("Failed to find GPU with Vulkan support.");
	}

	std::vector<VkPhysicalDevice> phys_devs(phys_dev_cnt);
	vkEnumeratePhysicalDevices(inst.handle, &phys_dev_cnt, phys_devs.data());

	std::multimap<uint32_t, VkPhysicalDevice> candidates;

	for(const VkPhysicalDevice& phys_dev : phys_devs) {
		if (phys_dev_is_suitable(phys_dev, surf)) {
			uint32_t scr = phys_dev_rate(phys_dev);
			candidates.insert(std::make_pair(scr, phys_dev));
		}
	}

	if (candidates.rbegin()->first > 0) {
		phys_dev->handle = candidates.rbegin()->second;
	} else {
		log_critical("Failed to Find any Suitable GPU.");
	}

	log_info("Selected GPU = ", phys_dev_get_name(*phys_dev));
}

VkPhysicalDeviceFeatures phys_dev_get_features(const phys_device_t &phys_dev) 
{
	VkPhysicalDeviceFeatures features = {};
	vkGetPhysicalDeviceFeatures(phys_dev.handle, &features);

	if (features.geometryShader != VK_TRUE) {
		log_critical("The found GPU doesn't have a Geometry Shader Feature.");
	}

	return features;
}

uint32_t phys_dev_find_mem_type(const phys_device_t &phys_dev, uint32_t type_filter, VkMemoryPropertyFlags props)
{
	VkPhysicalDeviceMemoryProperties mem_props = {};
	vkGetPhysicalDeviceMemoryProperties(phys_dev.handle, &mem_props);

	for(uint32_t i = 0; i < mem_props.memoryTypeCount; ++i) {
		if ((type_filter & (1 << i)) && (mem_props.memoryTypes[i].propertyFlags & props) == props) {
			return i;
		}
	}
	return -1;
}
