#include "core/vulkan/objects/device/QueueFamily.hpp"
#include "core/vulkan/objects/device/PhysicalDevice.hpp"
#include "core/vulkan/objects/instance/Surface.hpp"
#include "util/debug/Logger.hpp"

#include <vulkan/vulkan.h>

#include <vector>
#include <cstdint>

bool qf_is_complete(const queue_family_t &qf) 
{
    return qf.gfx.has_value() && qf.pres.has_value();
}

void qf_find(queue_family_t *qf, const phys_device_t &phys_dev, const surface_t &surface) 
{
	log_info("Searching a Suitable Queue Families...");

	uint32_t qf_count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(phys_dev.handle, &qf_count, nullptr);

	std::vector<VkQueueFamilyProperties> qfs(qf_count);
	vkGetPhysicalDeviceQueueFamilyProperties(phys_dev.handle, &qf_count, qfs.data());

	for (uint32_t i = 0; i < qf_count; ++i) {
		if (qfs[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			qf->gfx= i;
		}

		VkBool32 pres_supp = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(phys_dev.handle, i, surface.handle, &pres_supp);

		if (pres_supp) {
			qf->pres= i;
		} 

		if (qf_is_complete(*qf)) {
			break;
		}
	}

	if(!qf_is_complete(*qf)) {
		log_critical("Failed to Find any Suitable Queue Families.");
	}

	log_info("The Suitable Queue Families were Found.");
}
