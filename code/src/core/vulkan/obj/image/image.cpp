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
	info.mipLevels = img.mip_lvls;
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

void image_generate_mipmaps(const image &img, const device &dev, const physical_device &gpu, const queue &q, const command_pool &pool) 
{
	VkFormatProperties props;
	vkGetPhysicalDeviceFormatProperties(gpu.handle, img.fmt, &props);

	if (!(props.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)) 
		log_error("The Image Format does not Support Linear Bliting.");

	command_buffer cmd = command_buffer_begin_single_time_cmds(dev, pool);

	int32_t mip_w = img.extent.width;
	int32_t mip_h = img.extent.height;

	memory_barrier bar;
	bar.info = {};
	bar.info.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	bar.info.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	bar.info.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	bar.info.image = img.handle;
	bar.info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	bar.info.subresourceRange.baseArrayLayer = 0;
	bar.info.subresourceRange.layerCount = 1;
	bar.info.subresourceRange.levelCount = 1;

	for(uint32_t i = 1; i < img.mip_lvls; ++i) {
		bar.info.subresourceRange.baseMipLevel = i - 1;
		bar.info.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
		bar.info.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
		bar.info.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		bar.info.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;

		vkCmdPipelineBarrier(cmd.handle, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, nullptr, 0, nullptr, 1, &bar.info);

		VkImageBlit blit = {};
		blit.srcOffsets[0] = {0, 0, 0};
		blit.srcOffsets[1] = {mip_w, mip_h, 1};
		blit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		blit.srcSubresource.mipLevel = i - 1;
		blit.srcSubresource.baseArrayLayer = 0;
		blit.srcSubresource.layerCount = 1;

		blit.dstOffsets[0] = {0, 0, 0};
		blit.dstOffsets[1] = { mip_w > 1 ? mip_w / 2 : 1, mip_h > 1 ? mip_h / 2 : 1, 1};
		blit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		blit.dstSubresource.mipLevel = i;
		blit.dstSubresource.baseArrayLayer = 0;
		blit.dstSubresource.layerCount = 1;

		vkCmdBlitImage(cmd.handle, img.handle, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, img.handle, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &blit, VK_FILTER_LINEAR);

		bar.info.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
		bar.info.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		bar.info.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
		bar.info.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

		vkCmdPipelineBarrier(cmd.handle, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, nullptr, 0, nullptr, 1, &bar.info);

		if (mip_w > 1)
			mip_w /= 2;
		if (mip_h > 1)
			mip_h /= 2;
	}

	bar.info.subresourceRange.baseMipLevel = img.mip_lvls - 1;
	bar.info.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	bar.info.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	bar.info.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
	bar.info.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

	vkCmdPipelineBarrier(cmd.handle, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, nullptr, 0, nullptr, 1, &bar.info);

	command_buffer_end_single_time_cmds(cmd, dev, pool, q);
}
