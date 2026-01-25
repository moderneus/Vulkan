#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "core/vulkan/objects/device/PhysicalDevice.hpp"
#include "core/vulkan/objects/device/QueueFamily.hpp"
#include "core/vulkan/objects/device/Queue.hpp"
#include "util/debug/Logger.hpp"

#include <vulkan/vulkan.h>

#include <cstdint>

VkPhysicalDeviceFeatures device_get_enabled_features(const phys_device_t& phys_device) 
{
	VkPhysicalDeviceFeatures features = {};
	features.geometryShader = phys_device_get_features(phys_device).geometryShader;
	return features;
}

std::vector<VkDeviceQueueCreateInfo> device_create_queue_infos(const queue_family_t& queue_family, const float& queue_priority)
{
	log_info("Creating the Queue Infos...");

	std::vector<VkDeviceQueueCreateInfo> queue_infos;
	if (queue_family.graphics == queue_family.present) {
		queue_infos.push_back(device_create_queue_info(queue_family.graphics.value(), queue_priority));
	} else {
		queue_infos.push_back(device_create_queue_info(queue_family.graphics.value(), queue_priority));
		queue_infos.push_back(device_create_queue_info(queue_family.present.value(), queue_priority));
	}
	return queue_infos;

	log_info("The Queue Infos were Created.");
}

VkDeviceQueueCreateInfo device_create_queue_info(const uint32_t queue_family_idx, const float& queue_priority)
{
	log_info("Creating the Queue Info..."); 

	VkDeviceQueueCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	create_info.queueFamilyIndex = queue_family_idx;
	create_info.queueCount = 1;
	create_info.pQueuePriorities = &queue_priority;

	log_info("The Queue Info was Created.");

	return create_info;
}

VkDeviceCreateInfo device_create_info(const std::vector<VkDeviceQueueCreateInfo>& queue_infos, const VkPhysicalDeviceFeatures& phys_device_features) 
{
	log_info("Creating the Logical Device Info...");

	VkDeviceCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	create_info.queueCreateInfoCount = static_cast<uint32_t>(queue_infos.size());
	create_info.pQueueCreateInfos = queue_infos.data();
	create_info.pEnabledFeatures = &phys_device_features;
	create_info.enabledExtensionCount = static_cast<uint32_t>(phys_device_exts.size());
	create_info.ppEnabledExtensionNames = phys_device_exts.data();

	log_info("The Logical Device Info was Created.");

	return create_info;
}

void device_create(device_t* device, queue_t* queue, const queue_family_t& queue_family, const phys_device_t& phys_device)
{
	log_info("Creating a Logical Device...");

	const float queue_priority = 1.0f;
	std::vector<VkDeviceQueueCreateInfo> queue_infos = device_create_queue_infos(queue_family, queue_priority);
	VkPhysicalDeviceFeatures phys_device_features = device_get_enabled_features(phys_device);
	VkDeviceCreateInfo device_info = device_create_info(queue_infos, phys_device_features);

	if (vkCreateDevice(phys_device.handle, &device_info, nullptr, &device->handle) != VK_SUCCESS) {
		log_critical("Failed to Create the Logical Device!");
	}

	vkGetDeviceQueue(device->handle, queue_family.graphics.value(), 0, &queue->graphics);
	vkGetDeviceQueue(device->handle, queue_family.present.value(), 0, &queue->present);

	log_info("The Logical Device was created.");
}

void device_destroy(const device_t& device)
{
	log_info("Destroying the Logical Device...");

	if (device.handle == VK_NULL_HANDLE) {
		log_error("Cannot Destroy the Logical Device::Logical Device is not Created.");
	}
	
	vkDestroyDevice(device.handle, nullptr);

	log_info("The Logical Device was Destroyed.");
}
