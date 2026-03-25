#include "core/vulkan/obj/descriptor/descriptor_set_layout.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "util/debug/log.hpp"

VkDescriptorSetLayoutBinding descriptor_set_layout_create_binding(const VkDescriptorType type)
{
	log_info("Creating the Descriptor Set Layout Binding...");

	VkDescriptorSetLayoutBinding bind = {};
	bind.binding = 0;
	bind.descriptorType = type;
	bind.descriptorCount = 1;
	bind.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

	log_info("The Descriptor Set Layout Binding was Created.");

	return bind;
}

VkDescriptorSetLayoutCreateInfo descriptor_set_layout_create_info(const VkDescriptorSetLayoutBinding &bind)
{
	log_info("Creating the Descriptor Set Layout Info...");

	VkDescriptorSetLayoutCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	info.bindingCount = 1;
	info.pBindings = &bind;

	log_info("The Descriptor Set Layout Info was Created.");

	return info;
}

void descriptor_set_layout_create(descriptor_set_layout *set_lyt, const device &dev)
{
	log_info("Creating a Desriptor Set Layout...");

	VkDescriptorSetLayoutBinding bind = descriptor_set_layout_create_binding(set_lyt->type);
	VkDescriptorSetLayoutCreateInfo info = descriptor_set_layout_create_info(bind);

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
