#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "core/vulkan/objects/device/PhysicalDevice.hpp"
#include "core/vulkan/objects/device/QueueFamily.hpp"
#include "core/vulkan/objects/device/Queue.hpp"
#include "util/debug/Logger.hpp"

#include <vulkan/vulkan.h>

#include <cstdint>

VkPhysicalDeviceFeatures dev_get_enabled_features(const phys_device_t &phys_dev) 
{
	VkPhysicalDeviceFeatures features = {};
	features.geometryShader = phys_dev_get_features(phys_dev).geometryShader;
	return features;
}

VkDeviceQueueCreateInfo dev_create_q_info(const uint32_t qf_idx, const float &prior)
{
	log_info("Creating the Queue Info..."); 

	VkDeviceQueueCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	info.queueFamilyIndex = qf_idx;
	info.queueCount = 1;
	info.pQueuePriorities = &prior;

	log_info("The Queue Info was Created.");

	return info;
}

std::vector<VkDeviceQueueCreateInfo> dev_create_q_infos(const queue_family_t &qf, const float &prior)
{
	log_info("Creating the Queue Infos...");

	std::vector<VkDeviceQueueCreateInfo> infos;
	if (qf.gfx == qf.pres) {
		infos.push_back(dev_create_q_info(qf.gfx.value(), prior));
	} else {
		infos.push_back(dev_create_q_info(qf.gfx.value(), prior));
		infos.push_back(dev_create_q_info(qf.pres.value(), prior));
	}

	log_info("The Queue Infos were Created.");

	return infos;
}

VkDeviceCreateInfo dev_create_info(const std::vector<VkDeviceQueueCreateInfo> &q_infos, const VkPhysicalDeviceFeatures &features) 
{
	log_info("Creating the Logical Device Info...");

	VkDeviceCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	info.queueCreateInfoCount = static_cast<uint32_t>(q_infos.size());
	info.pQueueCreateInfos = q_infos.data();
	info.pEnabledFeatures = &features;
	info.enabledExtensionCount = static_cast<uint32_t>(phys_dev_exts.size());
	info.ppEnabledExtensionNames = phys_dev_exts.data();

	log_info("The Logical Device Info was Created.");

	return info;
}

void dev_create(device_t *dev, queue_t *q, const queue_family_t &qf, const phys_device_t &phys_dev)
{
	log_info("Creating a Logical Device...");

	const float q_prior = 1.0f;
	std::vector<VkDeviceQueueCreateInfo> q_infos = dev_create_q_infos(qf, q_prior);
	VkPhysicalDeviceFeatures features = dev_get_enabled_features(phys_dev);
	VkDeviceCreateInfo info = dev_create_info(q_infos, features);

	if (vkCreateDevice(phys_dev.handle, &info, nullptr, &dev->handle) != VK_SUCCESS) {
		log_critical("Failed to Create the Logical Device!");
	}

	vkGetDeviceQueue(dev->handle, qf.gfx.value(), 0, &q->gfx);
	vkGetDeviceQueue(dev->handle, qf.pres.value(), 0, &q->pres);

	log_info("The Logical Device was created.");
}

void dev_destroy(const device_t &dev)
{
	log_info("Destroying the Logical Device...");

	if (dev.handle == VK_NULL_HANDLE) {
		log_error("Cannot Destroy the Logical Device::Logical Device is not Created.");
	}
	
	vkDestroyDevice(dev.handle, nullptr);

	log_info("The Logical Device was Destroyed.");
}
