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

uint32_t physical_device_rate(const VkPhysicalDevice &gpu) 
{
	VkPhysicalDeviceProperties props;
	vkGetPhysicalDeviceProperties(gpu, &props);

	uint32_t scr = 0;

	if (props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		scr += 1000;

	scr += props.limits.maxImageDimension2D;

	return scr;
}

std::string physical_device_get_name(const physical_device &gpu)
{
	VkPhysicalDeviceProperties props;
	vkGetPhysicalDeviceProperties(gpu.handle, &props);
	return props.deviceName;
}

bool physical_device_check_ext_supp(const VkPhysicalDevice &gpu)
{
	uint32_t ext_cnt;
	vkEnumerateDeviceExtensionProperties(gpu, nullptr, &ext_cnt, nullptr);

	std::vector<VkExtensionProperties> exts(ext_cnt);
	vkEnumerateDeviceExtensionProperties(gpu, nullptr, &ext_cnt, exts.data());

	std::set<std::string> req_exts(physical_device_exts.begin(), physical_device_exts.end());

	for(const auto &ext : exts)
		req_exts.erase(ext.extensionName);

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
	

	log_info("Selected GPU = ", physical_device_get_name(*gpu));
}

VkPhysicalDeviceFeatures physical_device_get_features(const physical_device &gpu) 
{
	VkPhysicalDeviceFeatures features = {};
	vkGetPhysicalDeviceFeatures(gpu.handle, &features);

	if (features.geometryShader != VK_TRUE)
		log_critical("The found GPU doesn't have a Geometry Shader Feature.");

	return features;
}

uint32_t physical_device_find_mem_type(const physical_device &gpu, uint32_t type_filter, VkMemoryPropertyFlags props)
{
	VkPhysicalDeviceMemoryProperties mem_props = {};
	vkGetPhysicalDeviceMemoryProperties(gpu.handle, &mem_props);

	for(uint32_t i = 0; i < mem_props.memoryTypeCount; ++i) {
		if ((type_filter & (1 << i)) && (mem_props.memoryTypes[i].propertyFlags & props) == props)
			return i;
	}
	return -1;
}
