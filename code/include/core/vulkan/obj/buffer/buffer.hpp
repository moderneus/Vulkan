#ifndef MOD_BUFFER_HPP
#define MOD_BUFFER_HPP

#include "core/vulkan/obj/buffer/vertex.hpp"

#include "stb_image.h"

#include <vulkan/vulkan.h>

#include <vector>

struct command_pool;
struct physical_device;
struct device;
struct queue;
struct image;

struct buffer {
	VkBuffer		handle = VK_NULL_HANDLE;
	VkDeviceMemory		mem = VK_NULL_HANDLE;
	void			*data;
};

VkBufferCreateInfo buffer_create_info(const VkDeviceSize size, const VkBufferUsageFlags usage);

VkMemoryRequirements buffer_get_mem_reqs(const buffer &buf, const device &dev);

VkMemoryAllocateInfo buffer_create_alloc_info(const physical_device &gpu, const VkMemoryRequirements reqs);

void buffer_malloc(buffer *buf, const device &dev, const physical_device &gpu, const VkMemoryPropertyFlags props);

void buffer_memcpy(buffer *buf, const device &dev, const std::vector<vertex> &verts, const VkDeviceSize size);

void buffer_memcpy(buffer *buf, const device &dev, const std::vector<uint32_t> &idxs, const VkDeviceSize size);

void buffer_memcpy(buffer *buf, const device &dev, const image &img, const VkDeviceSize size);

void buffer_copy(const buffer &src_buf, const buffer &dst_buf, const device &dev, const queue &q, const command_pool &pool, const VkDeviceSize size);

void buffer_copy_to_image(const buffer &buf, const image &img, const device &dev, const command_pool &pool, const queue &q);

void buffer_create(buffer *buf, const device &dev, const physical_device &gpu, const VkDeviceSize size, const VkBufferUsageFlags usage, const VkMemoryPropertyFlags props);

void buffer_free(const buffer &buf, const device &dev);

void buffer_destroy(const buffer &buf, const device &dev);

#endif
