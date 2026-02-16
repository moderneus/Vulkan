#include "core/vulkan/obj/device/device.hpp"
#include "core/vulkan/obj/device/physical_device.hpp"
#include "core/vulkan/obj/device/queue_indices.hpp"
#include "core/vulkan/obj/device/queue.hpp"
#include "util/debug/log.hpp"

#include <vulkan/vulkan.h>

#include <cstdint>

VkPhysicalDeviceFeatures device_get_enabled_features(const physical_device &gpu) 
{
	VkPhysicalDeviceFeatures features = {};
	features.geometryShader = physical_device_get_features(gpu).geometryShader;
	return features;
}

VkDeviceQueueCreateInfo device_create_queue_info(const uint32_t q_idx, const float &prior)
{
	log_info("Creating the Queue Info..."); 

	VkDeviceQueueCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	info.queueFamilyIndex = q_idx;
	info.queueCount = 1;
	info.pQueuePriorities = &prior;

	log_info("The Queue Info was Created.");

	return info;
}

std::vector<VkDeviceQueueCreateInfo> device_create_queue_infos(const queue_indices &q_idx, const float &prior)
{
	log_info("Creating the Queue Infos...");

	std::vector<VkDeviceQueueCreateInfo> infos;
	if (q_idx.gfx == q_idx.pres) {
		infos.push_back(device_create_queue_info(q_idx.gfx.value(), prior));
	} else {
		infos.push_back(device_create_queue_info(q_idx.gfx.value(), prior));
		infos.push_back(device_create_queue_info(q_idx.pres.value(), prior));
	}

	log_info("The Queue Infos were Created.");

	return infos;
}

VkDeviceCreateInfo device_create_info(const std::vector<VkDeviceQueueCreateInfo> &q_infos, const VkPhysicalDeviceFeatures &features) 
{
	log_info("Creating the Logical Device Info...");

	VkDeviceCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	info.queueCreateInfoCount = static_cast<uint32_t>(q_infos.size());
	info.pQueueCreateInfos = q_infos.data();
	info.pEnabledFeatures = &features;
	info.enabledExtensionCount = static_cast<uint32_t>(physical_device_exts.size());
	info.ppEnabledExtensionNames = physical_device_exts.data();

	log_info("The Logical Device Info was Created.");

	return info;
}

void device_create(device *dev, queue *q, const queue_indices &q_idx, const physical_device &gpu)
{
	log_info("Creating a Logical Device...");

	const float q_prior = 1.0f;
	std::vector<VkDeviceQueueCreateInfo> q_infos = device_create_queue_infos(q_idx, q_prior);
	VkPhysicalDeviceFeatures features = device_get_enabled_features(gpu);
	VkDeviceCreateInfo info = device_create_info(q_infos, features);

	if (vkCreateDevice(gpu.handle, &info, nullptr, &dev->handle) != VK_SUCCESS)
		log_critical("Failed to Create the Logical Device!");

	vkGetDeviceQueue(dev->handle, q_idx.gfx.value(), 0, &q->gfx);
	vkGetDeviceQueue(dev->handle, q_idx.pres.value(), 0, &q->pres);

	log_info("The Logical Device was created.");
}

void device_destroy(const device &dev)
{
	log_info("Destroying the Logical Device...");

	if (dev.handle == VK_NULL_HANDLE)
		log_error("Cannot Destroy the Logical Device::Logical Device is not Created.");
	
	vkDestroyDevice(dev.handle, nullptr);

	log_info("The Logical Device was Destroyed.");
}
