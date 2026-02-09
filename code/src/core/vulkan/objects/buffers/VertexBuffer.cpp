#include "core/vulkan/objects/buffers/VertexBuffer.hpp"
#include "core/vulkan/objects/buffers/types/Vertex.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "core/vulkan/objects/device/PhysicalDevice.hpp"
#include "util/debug/Logger.hpp"

#include <cstring>

VkBufferCreateInfo vertex_buffer_create_info()
{
	VkBufferCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	create_info.size = sizeof(vertices[0]) * vertices.size();
	create_info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	return create_info;
}

VkMemoryRequirements vertex_buffer_get_mem_reqs(const vertex_buffer_t& buf, const device_t& device)
{
	VkMemoryRequirements mem_reqs = {};
	vkGetBufferMemoryRequirements(device.handle, buf.handle, &mem_reqs);
	return mem_reqs;
}

VkMemoryAllocateInfo vertex_buffer_create_alloc_info(const phys_device_t& phys_device, const VkMemoryRequirements mem_reqs)
{
	VkMemoryAllocateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	create_info.allocationSize = mem_reqs.size;
	create_info.memoryTypeIndex = phys_device_find_mem_type(phys_device, mem_reqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	return create_info;
}

void vertex_buffer_alloc_mem(vertex_buffer_mem_t* buf_mem, const vertex_buffer_t& buf, const device_t& device, const phys_device_t& phys_device)
{
	VkMemoryRequirements mem_reqs = vertex_buffer_get_mem_reqs(buf, device);
	VkMemoryAllocateInfo alloc_info = vertex_buffer_create_alloc_info(phys_device, mem_reqs);

	if (vkAllocateMemory(device.handle, &alloc_info, nullptr, &buf_mem->handle) != VK_SUCCESS) { 
		log_critical("Failed to Allocate Vertex Buffer Memory.");
	}
}

void vertex_buffer_mem_cpy(const vertex_buffer_mem_t& buf_mem, const device_t& device, const VkBufferCreateInfo info)
{
	void* data;
	vkMapMemory(device.handle, buf_mem.handle, 0, info.size, 0, &data);
		memcpy(data, vertices.data(), info.size);
	vkUnmapMemory(device.handle, buf_mem.handle);
}

void vertex_buffer_create(vertex_buffer_t* buf, vertex_buffer_mem_t* buf_mem, const device_t& device, const phys_device_t& phys_device)
{
	VkBufferCreateInfo buf_info = vertex_buffer_create_info();

	if (vkCreateBuffer(device.handle, &buf_info, nullptr, &buf->handle) != VK_SUCCESS) {
		log_critical("Failed to Create a Vertex Buffer.");
	}

	vertex_buffer_alloc_mem(buf_mem, *buf, device, phys_device);

	vkBindBufferMemory(device.handle, buf->handle, buf_mem->handle, 0);

	vertex_buffer_mem_cpy(*buf_mem, device, buf_info);
}

void vertex_buffer_mem_free(const vertex_buffer_mem_t& buf_mem, const device_t& device)
{
	if (buf_mem.handle == VK_NULL_HANDLE) {
		log_error("Failed to Free Vertex Buffer Memory::Vertex Buffer Memory is not Allocated.");
	}
	vkFreeMemory(device.handle, buf_mem.handle, nullptr);
}

void vertex_buffer_destroy(const vertex_buffer_t& buf, const vertex_buffer_mem_t& buf_mem, const device_t& device)
{
	if (buf.handle == VK_NULL_HANDLE) {
		log_error("Cannot Destroy the Vertex Buffer::Vertex Buffer is not Created.");
	}
	vkDestroyBuffer(device.handle, buf.handle, nullptr);

	vertex_buffer_mem_free(buf_mem, device);
}
