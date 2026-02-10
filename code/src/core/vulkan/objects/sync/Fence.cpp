#include "core/vulkan/objects/sync/Fence.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "util/debug/Logger.hpp"
#include "util/Constants.hpp"

VkFenceCreateInfo fence_create_info() 
{
	log_info("Creating the Fences Info...");

	VkFenceCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	info.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	log_info("The Fences Info were Created.");

	return info;
}

void fences_create(std::vector<fence_t> *fences, const device_t &dev) 
{
	log_info("Creating the Fences...");

	VkFenceCreateInfo info = fence_create_info();

	fences->resize(MAX_FRAMES_IN_FLIGHT);

	for(uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
		if (vkCreateFence(dev.handle, &info, nullptr, &fences->data()[i].handle) != VK_SUCCESS) {
			log_critical("Failed to Create the Fences.");
		}
	}

	log_info("The Fences were Created.");
}

void fences_destroy(const std::vector<fence_t> &fences, const device_t &dev) 
{
	log_info("Destroying the Fences...");

	for(uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
		if (fences[i].handle == VK_NULL_HANDLE) {
			log_error("Cannot Destroy the Fence::Fence is not Created.");
		}
		vkDestroyFence(dev.handle, fences[i].handle, nullptr);
	}

	log_info("The Fences were Destroyed.");
}
