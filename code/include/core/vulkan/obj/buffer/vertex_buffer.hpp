#ifndef MOD_VERTEX_BUFFER_HPP
#define MOD_VERTEX_BUFFER_HPP

#include <vulkan/vulkan.h>

struct phys_device_t;
struct device_t;

struct vertex_buffer_t
{
	VkBuffer handle = VK_NULL_HANDLE;
};

struct vertex_buffer_mem_t 
{
	VkDeviceMemory handle = VK_NULL_HANDLE;
};

VkBufferCreateInfo vert_buf_create_info();

VkMemoryRequirements vert_buf_get_mem_reqs(const vertex_buffer_t &buf, const device_t &dev);

VkMemoryAllocateInfo vert_buf_create_alloc_info(const phys_device_t &phys_dev, const VkMemoryRequirements reqs);

void vert_buf_alloc_mem(vertex_buffer_mem_t *mem, const vertex_buffer_t &buf, const device_t &dev, const phys_device_t &phys_dev);

void vert_buf_mem_cpy(const vertex_buffer_mem_t &mem, const device_t &dev, const VkBufferCreateInfo info);

void vert_buf_create(vertex_buffer_t *buf, vertex_buffer_mem_t *mem, const device_t &dev, const phys_device_t &phys_dev);

void vert_buf_mem_free(const vertex_buffer_mem_t &mem, const device_t &dev);

void vert_buf_destroy(const vertex_buffer_t &buf, const vertex_buffer_mem_t &mem, const device_t &dev);

#endif
