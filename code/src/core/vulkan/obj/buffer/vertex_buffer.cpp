#include "core/vulkan/obj/buffer/vertex_buffer.hpp"
#include "core/vulkan/obj/buffer/vertex.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "core/vulkan/obj/device/physical_device.hpp"
#include "util/debug/log.hpp"

#include <cstring>

VkBufferCreateInfo vertex_buffer_create_info()
{
	log_info("Creating the Vertex Buffer Info...");

	VkBufferCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	info.size = sizeof(triangle_verts[0]) * triangle_verts.size();
	info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	log_info("The Vertex Buffer Info was Created.");

	return info;
}

VkMemoryRequirements vertex_buffer_get_mem_reqs(const vertex_buffer &buf, const device &dev)
{
	log_info("Collecting the Vertex Buffer Memory Requirements...");

	VkMemoryRequirements reqs = {};
	vkGetBufferMemoryRequirements(dev.handle, buf.handle, &reqs);

	log_info("The Vertex Buffer Memory Requirements was Collected.");

	return reqs;
}

VkMemoryAllocateInfo vertex_buffer_create_alloc_info(const physical_device &gpu, const VkMemoryRequirements reqs)
{
	log_info("Creating the Vertex Buffer Allocation Info...");

	VkMemoryAllocateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	info.allocationSize = reqs.size;
	info.memoryTypeIndex = physical_device_find_mem_type(gpu, reqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | 
										       VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	log_info("The Vertex Buffer Allocation Info was Created.");

	return info;
}

void vertex_buffer_malloc(vertex_buffer_mem *mem, const vertex_buffer &buf, const device &dev, const physical_device &gpu)
{
	log_info("Allocation the Vertex Buffer Memory...");

	VkMemoryRequirements reqs = vertex_buffer_get_mem_reqs(buf, dev);
	VkMemoryAllocateInfo info = vertex_buffer_create_alloc_info(gpu, reqs);

	if (vkAllocateMemory(dev.handle, &info, nullptr, &mem->handle) != VK_SUCCESS)
		log_critical("Failed to Allocate Vertex Buffer Memory.");

	log_info("The Vertex Buffer Memory was Allocated.");
}

void vertex_buffer_memcpy(const vertex_buffer_mem &mem, const device &dev, const VkBufferCreateInfo info)
{
	log_info("Copying the Vertex Buffer Memory...");

	void* data;
	vkMapMemory(dev.handle, mem.handle, 0, info.size, 0, &data);
		memcpy(data, triangle_verts.data(), info.size);
	vkUnmapMemory(dev.handle, mem.handle);

	log_info("The Vertex Buffer Memory was Copyied.");
}

void vertex_buffer_create(vertex_buffer *buf, vertex_buffer_mem *mem, const device &dev, const physical_device &gpu)
{
	log_info("Creating a Vertex Buffer...");

	VkBufferCreateInfo info = vertex_buffer_create_info();

	if (vkCreateBuffer(dev.handle, &info, nullptr, &buf->handle) != VK_SUCCESS)
		log_critical("Failed to Create a Vertex Buffer.");

	vertex_buffer_malloc(mem, *buf, dev, gpu);

	vkBindBufferMemory(dev.handle, buf->handle, mem->handle, 0);

	vertex_buffer_memcpy(*mem, dev, info);

	log_info("The Vertex Buffer was Created.");
}

void vertex_buffer_free(const vertex_buffer_mem &mem, const device &dev)
{
	log_info("Freeing the Vertex Buffer Memory...");

	if (mem.handle == VK_NULL_HANDLE)
		log_error("Failed to Free Vertex Buffer Memory::Vertex Buffer Memory is not Allocated.");

	vkFreeMemory(dev.handle, mem.handle, nullptr);

	log_info("The Vertex Buffer Memory was Freed");
}

void vertex_buffer_destroy(const vertex_buffer &buf, const vertex_buffer_mem &mem, const device &dev)
{
	log_info("Destroying the Vertex Buffer...");

	if (buf.handle == VK_NULL_HANDLE)
		log_error("Cannot Destroy the Vertex Buffer::Vertex Buffer is not Created.");
	
	vkDestroyBuffer(dev.handle, buf.handle, nullptr);

	vertex_buffer_free(mem, dev);

	log_info("The Vertex Buffer was Destroyed.");
}
