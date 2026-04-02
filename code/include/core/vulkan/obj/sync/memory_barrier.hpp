#ifndef MOD_IMAGE_BARRIER_HPP
#define MOD_IMAGE_BARRIER_HPP

#include <vulkan/vulkan.h>

struct image;

struct memory_barrier {
	VkImageMemoryBarrier info = {};
};

void memory_barrier_create(memory_barrier *bar, const image &img, const VkImageLayout &old_lyt, const VkImageLayout &new_lyt, VkPipelineStateFlags *src_stage, VkPipelineStateFlags *dst_stage);

#endif
