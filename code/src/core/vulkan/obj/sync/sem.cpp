#include "core/vulkan/objects/sync/Semaphore.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "util/debug/Logger.hpp"
#include "util/Constants.hpp"

VkSemaphoreCreateInfo sem_create_info() 
{
	log_info("Creating the Semaphores Info...");

	VkSemaphoreCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	log_info("The Semaphores Info were Created.");

	return info;
}

void sems_create(std::vector<semaphore_t> *sems, const device_t &dev) 
{
	log_info("Creating the Semaphores...");

	VkSemaphoreCreateInfo info = sem_create_info();

	sems->resize(MAX_FRAMES_IN_FLIGHT);

	for(uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
		if (vkCreateSemaphore(dev.handle, &info, nullptr, &sems->data()[i].handle) != VK_SUCCESS) {
		    log_critical("Failed to Create the Semaphore.");
		}
	}

	log_info("The Semaphores were Created.");
}

void sems_destroy(const std::vector<semaphore_t> &sems, const device_t &dev) 
{
	log_info("Destroying the Semaphores...");

	for(uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
		if (sems[i].handle == VK_NULL_HANDLE) {
			log_error("Cannot Destroy the Semaphore::Semaphore is not Created.");
		}
		vkDestroySemaphore(dev.handle, sems[i].handle, nullptr);
	}

	log_info("The Semaphores were Destroyed.");
}
