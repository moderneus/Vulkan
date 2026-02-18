#include "core/vulkan/obj/sync/semaphore.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "util/debug/log.hpp"
#include "util/constants.hpp"

VkSemaphoreCreateInfo semaphore_create_info() 
{
	log_info("Creating the Semaphores Info...");

	VkSemaphoreCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	log_info("The Semaphores Info were Created.");

	return info;
}

void semaphores_create(std::vector<semaphore> *sems, const device &dev) 
{
	log_info("Creating the Semaphores...");

	VkSemaphoreCreateInfo info = semaphore_create_info();

	sems->resize(MAX_FRAMES_IN_FLIGHT);

	for(uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
		if (vkCreateSemaphore(dev.handle, &info, nullptr, &sems->data()[i].handle) != VK_SUCCESS)
		    log_critical("Failed to Create the Semaphore.");
	}

	log_info("The Semaphores were Created.");
}

void semaphores_destroy(const std::vector<semaphore> &sems, const device &dev) 
{
	log_info("Destroying the Semaphores...");

	for(uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
		if (sems[i].handle == VK_NULL_HANDLE)
			log_error("Cannot Destroy the Semaphore::Semaphore is not Created.");

		vkDestroySemaphore(dev.handle, sems[i].handle, nullptr);
	}

	log_info("The Semaphores were Destroyed.");
}
