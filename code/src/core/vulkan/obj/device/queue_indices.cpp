#include "core/vulkan/obj/device/queue_indices.hpp"
#include "core/vulkan/obj/device/physical_device.hpp"
#include "core/vulkan/obj/instance/surface.hpp"
#include "util/debug/log.hpp"

#include <vulkan/vulkan.h>

#include <vector>
#include <cstdint>

bool queue_indices_is_complete(const queue_indices &q_idx) 
{
	return q_idx.gfx.has_value() && q_idx.pres.has_value();
}

void queue_indices_find(queue_indices *q_idx, const physical_device &gpu, const surface &surf) 
{
	log_info("Searching a Suitable Queue Families...");

	uint32_t qf_cnt = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(gpu.handle, &qf_cnt, nullptr);

	std::vector<VkQueueFamilyProperties> qfs(qf_cnt);
	vkGetPhysicalDeviceQueueFamilyProperties(gpu.handle, &qf_cnt, qfs.data());

	for(uint32_t i = 0; i < qf_cnt; ++i) {
		if ((qfs[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) && (qfs[i].queueFlags & VK_QUEUE_COMPUTE_BIT))
			q_idx->gfx= i;

		VkBool32 pres_supp = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(gpu.handle, i, surf.handle, &pres_supp);

		if (pres_supp)
			q_idx->pres= i;

		if (queue_indices_is_complete(*q_idx))
			break;
	}

	if(!queue_indices_is_complete(*q_idx))
		log_critical("Failed to Find any Suitable Queue Families.");

	log_info("The Suitable Queue Families were Found.");
}
