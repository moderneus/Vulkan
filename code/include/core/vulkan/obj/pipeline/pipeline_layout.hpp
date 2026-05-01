#ifndef MOD_PIPELINE_LAYOUT_HPP
#define MOD_PIPELINE_LAYOUT_HPP

#include <vulkan/vulkan.h>

struct descriptor_set_layout;
struct device;

struct pipeline_layout {
	VkPipelineLayout handle = VK_NULL_HANDLE;
};

VkPipelineLayoutCreateInfo pipeline_layout_create_info(const descriptor_set_layout &set_lyt);

void pipeline_layout_create(pipeline_layout *lyt, const device &dev, const descriptor_set_layout &set_lyt);

void pipeline_layout_destroy(const pipeline_layout &lyt, const device &dev);

#endif
