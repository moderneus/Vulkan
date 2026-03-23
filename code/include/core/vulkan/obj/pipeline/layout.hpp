#ifndef MOD_LAYOUT_HPP
#define MOD_LAYOUT_HPP

#include <vulkan/vulkan.h>

struct descriptor_set_layout;
struct device;

struct layout {
	VkPipelineLayout handle = VK_NULL_HANDLE;
};

VkPipelineLayoutCreateInfo layout_create_info(const descriptor_set_layout &set_lyt);

void layout_create(layout *lyt, const device &dev, const descriptor_set_layout &set_lyt);

void layout_destroy(const layout &lyt, const device &dev);

#endif
