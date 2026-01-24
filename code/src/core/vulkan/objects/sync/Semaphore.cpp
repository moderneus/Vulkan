#include "core/vulkan/objects/sync/Semaphore.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "util/debug/Logger.hpp"
#include "util/Constants.hpp"

VkSemaphoreCreateInfo semaphore_create_info() 
{
	log_info("Creating the Semaphores Info...");

	VkSemaphoreCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	log_success("The Semaphores Info were Created!");

	return create_info;
}

void semaphores_create(std::vector<semaphore_t>* semaphores, const device_t& device) 
{
	log_info("Creating a Semaphores...");

	VkSemaphoreCreateInfo semaphore_info = semaphore_create_info();

	semaphores->resize(MAX_FRAMES_IN_FLIGHT);

	for(uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
		if(vkCreateSemaphore(device.handle, &semaphore_info, nullptr, &semaphores->data()[i].handle) != VK_SUCCESS) {
		    log_critical("Failed to Create the Semaphore!");
		}
	}

	log_success("The Semaphores were Created!");
}

void semaphores_destroy(const std::vector<semaphore_t>& semaphores, const device_t& device) 
{
	log_info("Destroying the Semaphores...");

	for(uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
		if(semaphores[i].handle == VK_NULL_HANDLE) {
			log_error("Cannot Destroy the Semaphore::Semaphore is not Created!");
		}
		vkDestroySemaphore(device.handle, semaphores[i].handle, nullptr);
	}

	log_success("The Semaphores were Destroyed!");
}
