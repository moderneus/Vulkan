#ifndef MOD_LAYOUT_HPP
#define MOD_LAYOUT_HPP

#include <vulkan/vulkan.h>

struct device_t;

struct pipeline_layout_t
{
	VkPipelineLayout handle = VK_NULL_HANDLE;
};

VkPipelineLayoutCreateInfo pipeline_layout_create_info();

void pipeline_layout_create(pipeline_layout_t *layout, const device_t &dev);

void pipeline_layout_destroy(const pipeline_layout_t &layout, const device_t &dev);

#endif
