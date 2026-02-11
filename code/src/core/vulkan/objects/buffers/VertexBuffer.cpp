#include "core/vulkan/objects/buffers/VertexBuffer.hpp"
#include "core/vulkan/objects/buffers/types/Vertex.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "core/vulkan/objects/device/PhysicalDevice.hpp"
#include "util/debug/Logger.hpp"

#include <cstring>

VkBufferCreateInfo vert_buf_create_info()
{
	log_info("Creating the Vertex Buffer Info...");

	VkBufferCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	info.size = sizeof(verts[0]) * verts.size();
	info.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	log_info("The Vertex Buffer Info was Created.");

	return info;
}

VkMemoryRequirements vert_buf_get_mem_reqs(const vertex_buffer_t &buf, const device_t &dev)
{
	log_info("Collecting the Vertex Buffer Memory Requirements...");

	VkMemoryRequirements reqs = {};
	vkGetBufferMemoryRequirements(dev.handle, buf.handle, &reqs);

	log_info("The Vertex Buffer Memory Requirements was Collected.");

	return reqs;
}

VkMemoryAllocateInfo vert_buf_create_alloc_info(const phys_device_t &phys_dev, const VkMemoryRequirements reqs)
{
	log_info("Creating the Vertex Buffer Allocation Info...");

	VkMemoryAllocateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	info.allocationSize = reqs.size;
	info.memoryTypeIndex = phys_dev_find_mem_type(phys_dev, reqs.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	log_info("The Vertex Buffer Allocation Info was Created.");

	return info;
}

void vert_buf_alloc_mem(vertex_buffer_mem_t *mem, const vertex_buffer_t &buf, const device_t &dev, const phys_device_t &phys_dev)
{
	log_info("Allocation the Vertex Buffer Memory...");

	VkMemoryRequirements reqs = vert_buf_get_mem_reqs(buf, dev);
	VkMemoryAllocateInfo info = vert_buf_create_alloc_info(phys_dev, reqs);

	if (vkAllocateMemory(dev.handle, &info, nullptr, &mem->handle) != VK_SUCCESS) { 
		log_critical("Failed to Allocate Vertex Buffer Memory.");
	}

	log_info("The Vertex Buffer Memory was Allocated.");
}

void vert_buf_mem_cpy(const vertex_buffer_mem_t &mem, const device_t &dev, const VkBufferCreateInfo info)
{
	log_info("Copying the Vertex Buffer Memory...");

	void* data;
	vkMapMemory(dev.handle, mem.handle, 0, info.size, 0, &data);
		memcpy(data, verts.data(), info.size);
	vkUnmapMemory(dev.handle, mem.handle);

	log_info("The Vertex Buffer Memory was Copyied.");
}

void vert_buf_create(vertex_buffer_t *buf, vertex_buffer_mem_t *mem, const device_t &dev, const phys_device_t &phys_dev)
{
	log_info("Creating a Vertex Buffer...");

	VkBufferCreateInfo info = vert_buf_create_info();

	if (vkCreateBuffer(dev.handle, &info, nullptr, &buf->handle) != VK_SUCCESS) {
		log_critical("Failed to Create a Vertex Buffer.");
	}

	vert_buf_alloc_mem(mem, *buf, dev, phys_dev);

	vkBindBufferMemory(dev.handle, buf->handle, mem->handle, 0);

	vert_buf_mem_cpy(*mem, dev, info);

	log_info("The Vertex Buffer was Created.");
}

void vert_buf_mem_free(const vertex_buffer_mem_t &mem, const device_t &dev)
{
	log_info("Freeing the Vertex Buffer Memory...");

	if (mem.handle == VK_NULL_HANDLE) {
		log_error("Failed to Free Vertex Buffer Memory::Vertex Buffer Memory is not Allocated.");
	}
	vkFreeMemory(dev.handle, mem.handle, nullptr);

	log_info("The Vertex Buffer Memory was Freed");
}

void vert_buf_destroy(const vertex_buffer_t &buf, const vertex_buffer_mem_t &mem, const device_t &dev)
{
	log_info("Destroying the Vertex Buffer...");

	if (buf.handle == VK_NULL_HANDLE) {
		log_error("Cannot Destroy the Vertex Buffer::Vertex Buffer is not Created.");
	}
	vkDestroyBuffer(dev.handle, buf.handle, nullptr);

	vert_buf_mem_free(mem, dev);

	log_info("The Vertex Buffer was Destroyed.");
}
