#ifndef MOD_DESCRIPTOR_POOL_HPP
#define MOD_DESCRIPTOR_POOL_HPP

struct device;

#include <vulkan/vulkan.h>

struct descriptor_pool {
	VkDescriptorPool handle = VK_NULL_HANDLE;
};

VkDescriptorPoolCreateInfo descriptor_pool_create_info(const VkDescriptorPoolSize &size);

VkDescriptorPoolSize descriptor_pool_create_size();

void descriptor_pool_create(descriptor_pool *pool, const device &dev);

void descriptor_pool_destroy(const descriptor_pool &pool, const device &dev);

#endif
