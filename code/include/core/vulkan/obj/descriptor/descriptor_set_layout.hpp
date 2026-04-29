#ifndef MOD_DESCRIPTOR_SET_LAYOUT_HPP
#define MOD_DESCRIPTOR_SET_LAYOUT_HPP

struct device;

#include <vulkan/vulkan.h>

#include <array>

struct descriptor_set_layout {
	VkDescriptorSetLayout handle = VK_NULL_HANDLE;
};

std::array<VkDescriptorSetLayoutBinding, 3> descriptor_set_layout_create_binding();

VkDescriptorSetLayoutCreateInfo descriptor_set_layout_create_info(const std::array<VkDescriptorSetLayoutBinding, 3> &binds);

void descriptor_set_layout_create(descriptor_set_layout *set_lyt, const device &dev);

void descriptor_set_layout_destroy(const descriptor_set_layout &set_lyt, const device &dev);

#endif
