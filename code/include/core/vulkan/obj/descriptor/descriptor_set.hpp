#ifndef MOD_DESCRIPTOR_SET_HPP
#define MOD_DESCRIPTOR_SET_HPP

#include <vulkan/vulkan.h>

#include <vector>
#include <array>

struct device;
struct descriptor_set_layout;
struct descriptor_pool;
struct uniform_buffer;
struct image_view;
struct sampler;

struct descriptor_set {
	VkDescriptorSet handle = VK_NULL_HANDLE;
};

VkDescriptorSetAllocateInfo descriptor_set_create_alloc_info(const std::vector<VkDescriptorSetLayout> &set_lyts, const descriptor_pool &pool);

VkDescriptorBufferInfo descriptor_set_create_buf_info(const uniform_buffer &buf);

VkDescriptorImageInfo descriptor_set_create_img_info(const image_view &view, const sampler &samp);

std::array<VkWriteDescriptorSet, 2> descriptor_set_create_write_infos(const descriptor_set &set, const VkDescriptorBufferInfo &buf_info, const VkDescriptorImageInfo &img_info);

void descriptor_sets_update(const descriptor_set &set, const device &dev, const uniform_buffer &buf, const image_view &view, const sampler &samp);

void descriptor_sets_create(std::vector<descriptor_set> *sets, const device &dev, const descriptor_pool &pool, const descriptor_set_layout &set_lyt, const std::vector<uniform_buffer> &bufs, const image_view &view, const sampler &samp);

#endif
