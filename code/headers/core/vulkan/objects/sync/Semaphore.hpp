#ifndef MOD_SEMAPHORE_HPP
#define MOD_SEMAPHORE_HPP

#include <vulkan/vulkan.h>

#include <vector>

struct device_t;

struct semaphore_t 
{
	VkSemaphore handle = VK_NULL_HANDLE;
};

VkSemaphoreCreateInfo semaphore_create_info();

void semaphores_create(std::vector<semaphore_t>* semaphores, const device_t& device);

void semaphores_destroy(const std::vector<semaphore_t>& semaphores, const device_t& device);

#endif
