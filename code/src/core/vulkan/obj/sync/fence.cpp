#include "core/vulkan/obj/sync/fence.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "util/debug/log.hpp"
#include "util/constants.hpp"

VkFenceCreateInfo fence_create_info() 
{
	log_info("Creating the Fences Info...");

	VkFenceCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	log_info("The Fences Info were Created.");

	return info;
}

void fences_create(std::vector<fence> *fns, const device &dev) 
{
	log_info("Creating the Fences...");

	VkFenceCreateInfo info = fence_create_info();

	fns->resize(MAX_FRAMES_IN_FLIGHT);

	for(uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
		if (vkCreateFence(dev.handle, &info, nullptr, &fns->data()[i].handle) != VK_SUCCESS)
			log_critical("Failed to Create the Fences.");
	}

	log_info("The Fences were Created.");
}

void fences_destroy(const std::vector<fence> &fns, const device &dev) 
{
	log_info("Destroying the Fences...");

	for(uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
		if (fns[i].handle == VK_NULL_HANDLE)
			log_error("Cannot Destroy the Fence::Fence is not Created.");

		vkDestroyFence(dev.handle, fns[i].handle, nullptr);
	}

	log_info("The Fences were Destroyed.");
}
