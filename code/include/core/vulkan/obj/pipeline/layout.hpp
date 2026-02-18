#ifndef MOD_LAYOUT_HPP
#define MOD_LAYOUT_HPP

#include <vulkan/vulkan.h>

struct device;

struct layout {
	VkPipelineLayout handle = VK_NULL_HANDLE;
};

VkPipelineLayoutCreateInfo layout_create_info();

void layout_create(layout *lyt, const device &dev);

void layout_destroy(const layout &lyt, const device &dev);

#endif
