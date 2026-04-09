#include "core/vulkan/obj/sync/memory_barrier.hpp"
#include "core/vulkan/obj/image/image.hpp"
#include "util/debug/log.hpp"

void memory_barrier_create(memory_barrier *bar, const image &img, const VkImageLayout &old_lyt, const VkImageLayout &new_lyt, VkPipelineStageFlags *src_stage, VkPipelineStageFlags *dst_stage)
{
	log_info("Creating a Memory Barrier...");

	bar->info = {};
	bar->info.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	bar->info.oldLayout = old_lyt;
	bar->info.newLayout = new_lyt;
	bar->info.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	bar->info.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	bar->info.image = img.handle;
	bar->info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	bar->info.subresourceRange.baseMipLevel = 0;
	bar->info.subresourceRange.levelCount = 1;
	bar->info.subresourceRange.baseArrayLayer = 0;
	bar->info.subresourceRange.layerCount = 1;

	if (old_lyt == VK_IMAGE_LAYOUT_UNDEFINED && new_lyt == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
		bar->info.srcAccessMask = 0;
		bar->info.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		
		*src_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		*dst_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
	} else if (old_lyt == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && new_lyt == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
		bar->info.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		bar->info.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

		*src_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		*dst_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
	} else {
		log_critical("Failed to Create Memory Barrier::Unsupported Layout Transition.");
	}

	log_info("The Memory Barrier was Created.");
}
