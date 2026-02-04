#ifndef MOD_PIPELINE_LAYOUT_HPP
#define MOD_PIPELINE_LAYOUT_HPP

#include <vulkan/vulkan.h>

struct device_t;

struct pipeline_layout_t
{
	VkPipelineLayout handle = VK_NULL_HANDLE;
};

VkPipelineLayoutCreateInfo pipeline_layout_create_info();

void pipeline_layout_create(pipeline_layout_t* pipeline_layout, const device_t& device);

void pipeline_layout_destroy(const pipeline_layout_t& pipeline_layout, const device_t& device);

#endif
