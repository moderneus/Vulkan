#include "core/vulkan/obj/image/image.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "core/vulkan/obj/device/physical_device.hpp"
#include "core/vulkan/obj/command/command_buffer.hpp"
#include "core/vulkan/obj/sync/memory_barrier.hpp"
#include "util/debug/log.hpp"

VkMemoryAllocateInfo image_create_alloc_info(const physical_device &gpu, const VkMemoryRequirements &reqs, const VkMemoryPropertyFlags &props)
{
	log_info("Creating the Image Allocate Info...");

	VkMemoryAllocateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	info.allocationSize = reqs.size;
	info.memoryTypeIndex = physical_device_find_mem_type(gpu, reqs.memoryTypeBits, props);

	log_info("The Image Allocate Info was Created.");

	return info;
}

VkImageCreateInfo image_create_info(const image &img)
{
	log_info("Creating the Image Info...");

	VkImageCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	info.imageType = VK_IMAGE_TYPE_2D;
	info.extent.width = img.extent.width;
	info.extent.height = img.extent.height;
	info.extent.depth = 1;
	info.mipLevels = 1;
	info.arrayLayers = 1;
	info.format = img.fmt;
	info.tiling = img.tiling;
	info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	info.usage = img.usage;
	info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	info.samples = VK_SAMPLE_COUNT_1_BIT;

	log_info("The Image Info was Created.");

	return info;
}

void image_malloc(image *img, const device &dev, const physical_device &gpu, const VkMemoryPropertyFlags &props)
{
	log_info("Allocating the Image Memory...");

	VkMemoryRequirements reqs;
	vkGetImageMemoryRequirements(dev.handle, img->handle, &reqs);

	VkMemoryAllocateInfo info = image_create_alloc_info(gpu, reqs, props);

	if (vkAllocateMemory(dev.handle, &info, nullptr, &img->mem) != VK_SUCCESS)
		log_error("Failed to Allocate the Image Memory");

	log_info("The Image Memory Was Allocated.");
}

void image_create(image *img, const device &dev, const physical_device &gpu, const VkMemoryPropertyFlags &props)
{
	log_info("Creating an Image...");

	VkImageCreateInfo info = image_create_info(*img);

	if (vkCreateImage(dev.handle, &info, nullptr, &img->handle) != VK_SUCCESS)
		log_error("Failed to Create the Image.");

	image_malloc(img, dev, gpu, props);

	vkBindImageMemory(dev.handle, img->handle, img->mem, 0);

	log_info("The Image was Created.");
}

void image_free(const image &img, const device &dev)
{
	log_info("Freeing the Image Memory...");
	
	if (img.mem == VK_NULL_HANDLE)
		log_info("Cannot Free the Image Memory::Image Memory is not Allocated.");

	vkFreeMemory(dev.handle, img.mem, nullptr);

	log_info("The Image Memory was Freed.");
}

void image_destroy(const image &img, const device &dev)
{
	log_info("Destroying the Image...");

	if (img.handle == VK_NULL_HANDLE)
		log_error("Cannot Destroy the Image::Image is not Created.");

	vkDestroyImage(dev.handle, img.handle, nullptr);

	image_free(img, dev);

	log_info("The Image was Destroyed.");
}

void image_transition_layout(const image &img, const device &dev, const queue &q, const command_pool &pool, const VkImageLayout &old_lyt, const VkImageLayout &new_lyt)
{
	log_info("Transitioning the Image Layout...");

	VkPipelineStageFlags src_stage;
	VkPipelineStageFlags dst_stage;

	memory_barrier bar = {};
	memory_barrier_create(&bar, img, old_lyt, new_lyt, &src_stage, &dst_stage);

	command_buffer cmd = command_buffer_begin_single_time_cmds(dev, pool);
		vkCmdPipelineBarrier(cmd.handle, src_stage, dst_stage, 0, 0, nullptr, 0, nullptr, 1, &bar.info);
	command_buffer_end_single_time_cmds(cmd, dev, pool, q);

	log_info("The Image Layout was Transitioned.");
}
