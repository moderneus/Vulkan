#include "core/vulkan/obj/descriptor/descriptor_pool.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "util/constants.hpp"
#include "util/debug/log.hpp"

VkDescriptorPoolCreateInfo descriptor_pool_create_info(const VkDescriptorPoolSize &size)
{
	log_info("Creating the Descriptor Pool Info...");

	VkDescriptorPoolCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	info.poolSizeCount = 1;
	info.pPoolSizes = &size;
	info.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

	log_info("The Descriptor Pool Info was Created.");
	
	return info;
}

VkDescriptorPoolSize descriptor_pool_create_size()
{
	log_info("Creating the Descriptor Pool Size Info...");

	VkDescriptorPoolSize size = {};
	size.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	size.descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

	log_info("The Descriptor Pool Size Info was Created.");
	
	return size;
}

void descriptor_pool_create(descriptor_pool *pool, const device &dev)
{
	log_info("Creating a Descriptor Pool...");

	VkDescriptorPoolSize size = descriptor_pool_create_size();
	VkDescriptorPoolCreateInfo info = descriptor_pool_create_info(size);

	if (vkCreateDescriptorPool(dev.handle, &info, nullptr, &pool->handle) != VK_SUCCESS)
		log_critical("Failed to Create the Descriptor Pool.");

	log_info("The Descriptor Pool was Created.");
}

void descriptor_pool_destroy(const descriptor_pool &pool, const device &dev)
{
	log_info("Destroying the Descriptor Pool...");

	if (pool.handle == VK_NULL_HANDLE)
		log_error("Cannot Destroy the Descriptor Pool::Descriptor Pool is not Created.");

	vkDestroyDescriptorPool(dev.handle, pool.handle, nullptr);

	log_info("The Descriptor Pool was Destroyed.");
}
