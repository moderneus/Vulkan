#include "core/vulkan/obj/descriptor/descriptor_pool.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "util/constants.hpp"
#include "util/debug/log.hpp"

VkDescriptorPoolCreateInfo descriptor_pool_create_info(const std::array<VkDescriptorPoolSize, 2> &sizes)
{
	log_info("Creating the Descriptor Pool Info...");

	VkDescriptorPoolCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	info.poolSizeCount = static_cast<uint32_t>(sizes.size());
	info.pPoolSizes = sizes.data();
	info.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

	log_info("The Descriptor Pool Info was Created.");
	
	return info;
}

std::array<VkDescriptorPoolSize, 2> descriptor_pool_create_sizes()
{
	log_info("Creating the Descriptor Pool Size Info...");

	std::array<VkDescriptorPoolSize, 2> sizes = {};

	sizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	sizes[0].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

	sizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	sizes[1].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

	log_info("The Descriptor Pool Size Info was Created.");
	
	return sizes;
}

void descriptor_pool_create(descriptor_pool *pool, const device &dev)
{
	log_info("Creating a Descriptor Pool...");

	std::array<VkDescriptorPoolSize, 2> sizes = descriptor_pool_create_sizes();
	VkDescriptorPoolCreateInfo info = descriptor_pool_create_info(sizes);

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
