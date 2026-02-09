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

VkBufferCreateInfo vertex_buffer_create_info();

VkMemoryRequirements vertex_buffer_get_mem_reqs(const vertex_buffer_t& buf, const device_t& device);

VkMemoryAllocateInfo vertex_buffer_create_alloc_info(const phys_device_t& phys_device, const VkMemoryRequirements mem_reqs);

void vertex_buffer_alloc_mem(vertex_buffer_mem_t* buf_mem, const vertex_buffer_t& buf, const device_t& device, const phys_device_t& phys_device);

void vertex_buffer_mem_cpy(const vertex_buffer_mem_t& buf_mem, const device_t& device, const VkBufferCreateInfo info);

void vertex_buffer_create(vertex_buffer_t* buf, vertex_buffer_mem_t* buf_mem, const device_t& device, const phys_device_t& phys_device);

void vertex_buffer_mem_free(const vertex_buffer_mem_t& buf_mem, const device_t& device);

void vertex_buffer_destroy(const vertex_buffer_t& buf, const vertex_buffer_mem_t& buf_mem, const device_t& device);

#endif
