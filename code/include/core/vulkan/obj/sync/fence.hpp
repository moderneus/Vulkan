#ifndef MOD_FENCE_HPP
#define MOD_FENCE_HPP

#include <vulkan/vulkan.h>

#include <vector>

struct device;

struct fence {
	VkFence handle = VK_NULL_HANDLE;
};

VkFenceCreateInfo fence_create_info();

void fences_create(std::vector<fence> *fns, const device &dev);

void fences_destroy(const std::vector<fence> &fns, const device &dev);

#endif
