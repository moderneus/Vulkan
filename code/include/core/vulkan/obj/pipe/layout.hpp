#ifndef MOD_LAYOUT_HPP
#define MOD_LAYOUT_HPP

#include <vulkan/vulkan.h>

struct device_t;

struct layout_t
{
	VkPipelineLayout handle = VK_NULL_HANDLE;
};

VkPipelineLayoutCreateInfo layout_create_info();

void layout_create(layout_t *layout, const device_t &dev);

void layout_destroy(const layout_t &layout, const device_t &dev);

#endif
