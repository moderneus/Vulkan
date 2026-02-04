#ifndef MOD_FENCE_HPP
#define MOD_FENCE_HPP

#include <vulkan/vulkan.h>

#include <vector>

struct device_t;

struct fence_t
{
	VkFence handle = VK_NULL_HANDLE;
};

VkFenceCreateInfo fence_create_info();

void fences_create(std::vector<fence_t>* fences, const device_t& device);

void fences_destroy(const std::vector<fence_t>& fences, const device_t& device);

#endif
