#include "core/vulkan/obj/descriptor/descriptor_set_layout.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "util/debug/log.hpp"

std::array<VkDescriptorSetLayoutBinding, 2> descriptor_set_layout_create_bindings()
{
	log_info("Creating the Descriptor Set Layout Binding...");

	VkDescriptorSetLayoutBinding ubo_bind = {};
	ubo_bind.binding = 0;
	ubo_bind.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	ubo_bind.descriptorCount = 1;
	ubo_bind.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

	VkDescriptorSetLayoutBinding samp_bind = {};
	samp_bind.binding = 1;
	samp_bind.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	samp_bind.descriptorCount = 1;
	samp_bind.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

	log_info("The Descriptor Set Layout Binding was Created.");

	return {ubo_bind, samp_bind};
}

VkDescriptorSetLayoutCreateInfo descriptor_set_layout_create_info(const std::array<VkDescriptorSetLayoutBinding, 2> &binds)
{
	log_info("Creating the Descriptor Set Layout Info...");

	VkDescriptorSetLayoutCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	info.bindingCount = static_cast<uint32_t>(binds.size());
	info.pBindings = binds.data();

	log_info("The Descriptor Set Layout Info was Created.");

	return info;
}

void descriptor_set_layout_create(descriptor_set_layout *set_lyt, const device &dev)
{
	log_info("Creating a Desriptor Set Layout...");

	std::array<VkDescriptorSetLayoutBinding, 2> binds = descriptor_set_layout_create_bindings();
	VkDescriptorSetLayoutCreateInfo info = descriptor_set_layout_create_info(binds);

	if (vkCreateDescriptorSetLayout(dev.handle, &info, nullptr, &set_lyt->handle) != VK_SUCCESS)
		log_critical("Failed to Create the Descriptor Set Layout.");

	log_info("The Descriptor Set Layout was Created.");
}

void descriptor_set_layout_destroy(const descriptor_set_layout &set_lyt, const device &dev)
{
	log_info("Destroying the Descriptor Set Layout...");

	if (set_lyt.handle == VK_NULL_HANDLE)
		log_error("Cannot Destroy the Descriptor Set Layout::Descriptor Set Layout is not Created.");

	vkDestroyDescriptorSetLayout(dev.handle, set_lyt.handle, nullptr);

	log_info("The Descriptor Set Layout was Destroyed."); 
}
