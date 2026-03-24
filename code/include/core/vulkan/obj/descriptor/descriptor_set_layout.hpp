#ifndef MOD_DESCRIPTOR_SET_LAYOUT_HPP
#define MOD_DESCRIPTOR_SET_LAYOUT_HPP

struct device;

#include <vulkan/vulkan.h>

struct descriptor_set_layout {
	VkDescriptorSetLayout		handle = VK_NULL_HANDLE;
	VkDescriptorType		type;
};

VkDescriptorSetLayoutBinding descriptor_set_layout_create_binding(const VkDescriptorType type);

VkDescriptorSetLayoutCreateInfo descriptor_set_layout_create_info(const VkDescriptorSetLayoutBinding &bind);

void descriptor_set_layout_create(descriptor_set_layout *set_lyt, const device &dev);

void descriptor_set_layout_destroy(const descriptor_set_layout &set_lyt, const device &dev);

#endif
