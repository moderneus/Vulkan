#ifndef MOD_DESCRIPTOR_POOL_HPP
#define MOD_DESCRIPTOR_POOL_HPP

struct device;

#include <vulkan/vulkan.h>

#include <array>

struct descriptor_pool {
	VkDescriptorPool handle = VK_NULL_HANDLE;
};

VkDescriptorPoolCreateInfo descriptor_pool_create_info(const std::array<VkDescriptorPoolSize, 2> &sizes);

std::array<VkDescriptorPoolSize, 2> descriptor_pool_create_sizes();

void descriptor_pool_create(descriptor_pool *pool, const device &dev);

void descriptor_pool_destroy(const descriptor_pool &pool, const device &dev);

#endif
