#ifndef MOD_VERTEX_BUFFER_HPP
#define MOD_VERTEX_BUFFER_HPP

#include <vulkan/vulkan.h>

struct physical_device;
struct device;

struct vertex_buffer
{
	VkBuffer handle = VK_NULL_HANDLE;
};

struct vertex_buffer_mem
{
	VkDeviceMemory handle = VK_NULL_HANDLE;
};

VkBufferCreateInfo vertex_buffer_create_info();

VkMemoryRequirements vertex_buffer_get_mem_reqs(const vertex_buffer &buf, const device &dev);

VkMemoryAllocateInfo vertex_buffer_create_alloc_info(const physical_device &gpu, const VkMemoryRequirements reqs);

void vertex_buffer_malloc(vertex_buffer_mem *mem, const vertex_buffer &buf, const device &dev, const physical_device &gpu);

void vertex_buffer_memcpy(const vertex_buffer_mem &mem, const device &dev, const VkBufferCreateInfo info);

void vertex_buffer_create(vertex_buffer *buf, vertex_buffer_mem *mem, const device &dev, const physical_device &gpu);

void vertex_buffer_free(const vertex_buffer_mem &mem, const device &dev);

void vertex_buffer_destroy(const vertex_buffer &buf, const vertex_buffer_mem &mem, const device &dev);

#endif
