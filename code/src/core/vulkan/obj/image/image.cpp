#include "core/vulkan/obj/image/image.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "core/vulkan/obj/device/physical_device.hpp"
#include "core/vulkan/obj/command/command_buffer.hpp"
#include "core/vulkan/obj/sync/memory_barrier.hpp"
#include "util/debug/log.hpp"

VkMemoryAllocateInfo image_create_alloc_info(const physical_device &gpu, const VkMemoryRequirements &reqs, const VkMemoryPropertyFlags &props)
{
	VkMemoryAllocate info = {};
	info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	info.allocationSize = reqs.size;
	info.memoryTypeIndex = physical_device_find_mem_type(gpu, reqs.memoryTypeBits, props);
	return info;
}

VkImageCreateInfo image_create_info(const image &img)
{
	VkImageCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	info.imageType = VK_IMAGE_TYPE_2D;
	info.extent.width = img.width;
	info.extent.height = img.height;
	info.extent.depth = 1;
	info.mipLevels = 1;
	info.arrayLayers = 1;
	info.format = img.fmt;
	info.tiling = img.tiling;
	info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	info.usage = img.usage;
	info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	info.samples = VK_SAMPLE_COUNT_1_BIT;
	return info;
}

void image_create(image *img, const device &dev, const physical_device &gpu, const VkMemoryPropertyFlags &props)
{
	VkImageCreateInfo info = image_create_info(*img);

	if (vkCreateImage(dev.handle, &info, nullptr, &img->handle) != VK_SUCESS)
		log_error("Failed to Create the Image.");

	VkMemoryRequirements reqs;
	vkGetImageMemoryRequirements(dev.handle, img.handle, &reqs);

	VkMemoryAllocateInfo alloc_info = image_create_alloc_info(gpu, reqs, props);

	if (vkAllocateMemory(dev.handle, &alloc_info, nullptr, &img->mem) != VK_SUCCESS)
		log_error("Failed to Allocate the Image Memory");

	vkBindImageMemory(dev.handle, img.handle, img.mem, 0);
}

void image_destroy(const image &img, const device &dev)
{
	vkDestroyImage(dev.handle, img.handle, nullptr);
	vkFreeMemory(dev.handle, img.mem, nullptr);
}

void image_transition_layout(const image &img, const device &dev, const queue &q, const command_pool &pool, const VkImageLayout &old_lyt, const VkImageLayout &new_lyt)
{
	VkPipelineStateFlags src_stage;
	VkPipelineStateFlags dst_stage;

	memory_barrier bar = {};
	memory_barrier_create(&bar, img, old_lyt, new_lyt, &src_stage, &dst_stage);

	command_buffer cmd = command_buffer_begin_single_time_cmds(dev);
		VkCmdPipelineBarrier(cmd.handle, src_stage, dst_stage, 0, nullptr, 0, nullptr, 1, &bar.info);
	command_buffer_end_single_time_cmds(cmd, dev, pool, q);
}
