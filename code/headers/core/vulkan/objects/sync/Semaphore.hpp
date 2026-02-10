#ifndef MOD_SEMAPHORE_HPP
#define MOD_SEMAPHORE_HPP

#include <vulkan/vulkan.h>

#include <vector>

struct device_t;

struct semaphore_t 
{
	VkSemaphore handle = VK_NULL_HANDLE;
};

VkSemaphoreCreateInfo sem_create_info();

void sem_create(std::vector<semaphore_t> *sems, const device_t &dev);

void sem_destroy(const std::vector<semaphore_t> &sems, const device_t &dev);

#endif
