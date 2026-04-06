#include "core/vulkan/obj/buffer/vertex_buffer.hpp"
#include "core/vulkan/obj/buffer/vertex.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "core/vulkan/obj/device/queue.hpp"
#include "core/vulkan/obj/device/physical_device.hpp"
#include "core/vulkan/obj/command/command_pool.hpp"
#include "core/vulkan/obj/command/command_buffer.hpp"
#include "core/vulkan/obj/image/image.hpp"
#include "util/debug/log.hpp"

#include "stb_image.h"

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

	command_buffer cmd = command_buffer_begin_single_time_cmds(dev, pool);

		VkBufferCopy copy_region = {};
		copy_region.size = size;

		vkCmdCopyBuffer(cmd.handle, src_buf.handle, dst_buf.handle, 1, &copy_region);

	command_buffer_end_single_time_cmds(cmd, dev, pool, q);

	log_info("The Buffer was Copied.");
}

void buffer_copy_to_image(const buffer &buf, const image &img, const device &dev, const command_pool &pool, const queue &q)
{
	command_buffer cmd = command_buffer_begin_single_time_cmds(dev, pool);

	VkBufferImageCopy region = {};
	region.bufferOffset = 0;
	region.bufferRowLength = 0;
	region.bufferImageHeight = 0;
	region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	region.imageSubresource.mipLevel = 0;
	region.imageSubresource.baseArrayLayer = 0;
	region.imageSubresource.layerCount = 1;
	region.imageOffset = {0, 0, 0};
	region.imageExtent = {img.extent.width, img.extent.height, 1};

	vkCmdCopyBufferToImage(cmd.handle, buf.handle, img.handle, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
	
	command_buffer_end_single_time_cmds(cmd, dev, pool, q);
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

void buffer_memcpy(buffer *buf, const device &dev, const image &img, const VkDeviceSize size)
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
