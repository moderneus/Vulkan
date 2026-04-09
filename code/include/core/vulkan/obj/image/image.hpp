#ifndef MOD_IMAGE_HPP
#define MOD_IMAGE_HPP

#include <vulkan/vulkan.h>

#include "stb_image.h"

struct device;
struct queue;
struct physical_device;
struct command_pool;
struct command_buffer;

struct image {
	VkImage				handle = VK_NULL_HANDLE;
	VkDeviceMemory			mem = VK_NULL_HANDLE;
	stbi_uc				*data;
	VkExtent2D			extent;
	uint32_t			channels;
	VkImageUsageFlags		usage;
	VkImageTiling			tiling;
	VkFormat			fmt;
};

VkMemoryAllocateInfo image_create_alloc_info(const physical_device &gpu, const VkMemoryRequirements &reqs, const VkMemoryPropertyFlags &props);

VkImageCreateInfo image_create_info(const image &img);

void image_malloc(image *img, const device &dev, const physical_device &gpu, const VkMemoryPropertyFlags &props);

void image_create(image *img, const device &dev, const physical_device &gpu, const VkMemoryPropertyFlags &props);

void image_destroy(const image &img, const device &dev);

void image_transition_layout(const image &img, const device &dev, const queue &q, const command_pool &pool, const VkImageLayout &old_lyt, const VkImageLayout &new_lyt);

#endif
