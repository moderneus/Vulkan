#ifndef MOD_SEMAPHORE_HPP
#define MOD_SEMAPHORE_HPP

#include <vulkan/vulkan.h>

#include <vector>

struct device;

struct semaphore {
	VkSemaphore handle = VK_NULL_HANDLE;
};

VkSemaphoreCreateInfo semaphore_create_info();

void semaphores_create(std::vector<semaphore> *sems, const device &dev);

void semaphores_destroy(const std::vector<semaphore> &sems, const device &dev);

#endif
