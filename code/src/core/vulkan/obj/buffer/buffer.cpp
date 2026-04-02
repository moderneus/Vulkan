#include "core/vulkan/obj/buffer/vertex_buffer.hpp"
#include "core/vulkan/obj/buffer/vertex.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "core/vulkan/obj/device/queue.hpp"
#include "core/vulkan/obj/device/physical_device.hpp"
#include "core/vulkan/obj/command/command_pool.hpp"
#include "core/vulkan/obj/command/command_buffer.hpp"
#include "core/vulkan/obj/image/image.hpp"
#include "util/debug/log.hpp"

#include "stbi_image.h"

#include <cstring>

VkBufferCreateInfo buffer_create_info(const VkDeviceSize size, const VkBufferUsageFlags usage)
{
	log_info("Creating the Vertex Buffer Info...");

	VkBufferCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	info.size = size;
	info.usage = usage;
	info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	log_info("The Vertex Buffer Info was Created.");

	return info;
}

VkMemoryRequirements buffer_get_mem_reqs(const buffer &buf, const device &dev)
{
	log_info("Collecting the Vertex Buffer Memory Requirements...");

	VkMemoryRequirements reqs = {};
	vkGetBufferMemoryRequirements(dev.handle, buf.handle, &reqs);

	log_info("The Vertex Buffer Memory Requirements was Collected.");

	return reqs;
}

VkMemoryAllocateInfo buffer_create_alloc_info(const physical_device &gpu, const VkMemoryRequirements reqs, const VkMemoryPropertyFlags props)
{
	log_info("Creating the Vertex Buffer Allocation Info...");

	VkMemoryAllocateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	info.allocationSize = reqs.size;
	info.memoryTypeIndex = physical_device_find_mem_type(gpu, reqs.memoryTypeBits, props);

	log_info("The Vertex Buffer Allocation Info was Created.");

	return info;
}

void buffer_malloc(buffer *buf, const device &dev, const physical_device &gpu, const VkMemoryPropertyFlags props)
{
	log_info("Allocating the Vertex Buffer Memory...");

	VkMemoryRequirements reqs = buffer_get_mem_reqs(*buf, dev);
	VkMemoryAllocateInfo info = buffer_create_alloc_info(gpu, reqs, props);

	if (vkAllocateMemory(dev.handle, &info, nullptr, &buf->mem) != VK_SUCCESS)
		log_critical("Failed to Allocate Vertex Buffer Memory.");

	log_info("The Vertex Buffer Memory was Allocated.");
}

void buffer_copy(const buffer &src_buf, const buffer &dst_buf, const device &dev, const queue &q, const command_pool &pool, const VkDeviceSize size)
{
	log_info("Copying the Buffer...");

	VkCommandBufferAllocateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	info.commandPool = pool.handle;
	info.commandBufferCount = 1;

	command_buffer cmd;
	vkAllocateCommandBuffers(dev.handle, &info, &cmd.handle);

	VkCommandBufferBeginInfo begin_info = {};
	begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(cmd.handle, &begin_info);
		VkBufferCopy copy_region = {};
		copy_region.size = size;
		vkCmdCopyBuffer(cmd.handle, src_buf.handle, dst_buf.handle, 1, &copy_region);
	vkEndCommandBuffer(cmd.handle);

	VkSubmitInfo submit_info = {};
	submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submit_info.commandBufferCount = 1;
	submit_info.pCommandBuffers = &cmd.handle;

	vkQueueSubmit(q.gfx, 1, &submit_info, VK_NULL_HANDLE);
	vkQueueWaitIdle(q.gfx);

	vkFreeCommandBuffers(dev.handle, pool.handle, 1, &cmd.handle);

	log_info("The Buffer was Copied.");
}

void buffer_memcpy(buffer *buf, const device &dev, const std::vector<vertex> &verts, const VkDeviceSize size)
{
	log_info("Copying the Vertex Buffer Memory...");

	vkMapMemory(dev.handle, buf->mem, 0, size, 0, &buf->data);
		memcpy(buf->data, verts.data(), static_cast<size_t>(size));
	vkUnmapMemory(dev.handle, buf->mem);

	log_info("The Vertex Buffer Memory was Copyied.");
}

void buffer_memcpy(buffer *buf, const device &dev, const std::vector<uint32_t> &idxs, const VkDeviceSize size)
{
	log_info("Copying the Index Buffer Memory...");

	vkMapMemory(dev.handle, buf->mem, 0, size, 0, &buf->data);
		memcpy(buf->data, idxs.data(), static_cast<size_t>(size));
	vkUnmapMemory(dev.handle, buf->mem);

	log_info("The Index Buffer Memory was Copyied.");
}

void buffer_memcpy(buffer *buf, const device &dev, const image &img, const VkDeviceSize)
{
	log_info("Copying the Image...");

	vkMapMemory(dev.handle, buf->mem, 0, size, 0, &buf->data);
		memcpy(buf->data, img.data, static_cast<size_t>(size));
	vkUnmapMemory(dev.handle, buf->mem);

	log_info("The Image was Copyied.");
}

void buffer_create(buffer *buf, const device &dev, const physical_device &gpu, const VkDeviceSize size, const VkBufferUsageFlags usage, const VkMemoryPropertyFlags props)
{
	log_info("Creating a Vertex Buffer...");

	VkBufferCreateInfo info = buffer_create_info(size, usage);

	if (vkCreateBuffer(dev.handle, &info, nullptr, &buf->handle) != VK_SUCCESS)
		log_critical("Failed to Create a Vertex Buffer.");

	buffer_malloc(buf, dev, gpu, props);

	vkBindBufferMemory(dev.handle, buf->handle, buf->mem, 0);

	log_info("The Vertex Buffer was Created.");
}

void buffer_free(const buffer &buf, const device &dev)
{
	log_info("Freeing the Vertex Buffer Memory...");

	if (buf.mem == VK_NULL_HANDLE)
		log_error("Failed to Free Vertex Buffer Memory::Vertex Buffer Memory is not Allocated.");

	vkFreeMemory(dev.handle, buf.mem, nullptr);

	log_info("The Vertex Buffer Memory was Freed");
}

void buffer_destroy(const buffer &buf, const device &dev)
{
	log_info("Destroying the Vertex Buffer...");

	if (buf.handle == VK_NULL_HANDLE)
		log_error("Cannot Destroy the Vertex Buffer::Vertex Buffer is not Created.");
	
	vkDestroyBuffer(dev.handle, buf.handle, nullptr);

	buffer_free(buf, dev);

	log_info("The Vertex Buffer was Destroyed.");
}
