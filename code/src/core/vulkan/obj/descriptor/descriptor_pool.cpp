#include "core/vulkan/obj/descriptor/descriptor_pool.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "util/constants.hpp"
#include "util/debug/log.hpp"

VkDescriptorPoolCreateInfo descriptor_pool_create_info(const VkDescriptorPoolSize &size)
{
	VkDescriptorPoolCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	info.poolSizeCount = 1;
	info.pPoolSizes = &size;
	info.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
	return info;
}

VkDescriptorPoolSize descriptor_pool_create_size()
{
	VkDescriptorPoolSize size = {};
	size.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	size.descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
	return size;
}

void descriptor_pool_create(descriptor_pool *pool, const device &dev)
{
	VkDescriptorPoolSize size = descriptor_pool_create_size();
	VkDescriptorPoolCreateInfo info = descriptor_pool_create_info(size);

	if (vkCreateDescriptorPool(dev.handle, &info, nullptr, &pool->handle) != VK_SUCCESS)
		log_critical("Failed to Create the Descriptor Pool.");
}

void descriptor_pool_destroy(const descriptor_pool &pool, const device &dev)
{
	if (pool.handle == VK_NULL_HANDLE)
		log_error("Cannot Destroy the Descriptor Pool::Descriptor Pool is not Created.");

	vkDestroyDescriptorPool(dev.handle, pool.handle, nullptr);
}
