#ifndef MOD_DESCRIPTOR_SET_HPP
#define MOD_DESCRIPTOR_SET_HPP

#include <vulkan/vulkan.h>

#include <vector>
#include <array>

struct device;
struct descriptor_set_layout;
struct shader_storage_buffer;
struct descriptor_pool;
struct uniform_buffer;
struct image_view;
struct sampler;
struct ssbos;

struct descriptor_set {
	VkDescriptorSet handle = VK_NULL_HANDLE;
};

VkDescriptorSetAllocateInfo descriptor_set_create_alloc_info(const std::vector<VkDescriptorSetLayout> &set_lyts, const descriptor_pool &pool);

std::array<VkDescriptorBufferInfo, 3> descriptor_set_create_bufs_info(const uint32_t &idx, const uniform_buffer &buf, const std::vector<shader_storage_buffer> &ssbos);

VkDescriptorImageInfo descriptor_set_create_img_info(const image_view &view, const sampler &samp);

std::array<VkWriteDescriptorSet, 3> descriptor_set_create_write_infos(const descriptor_set &set, const std::array<VkDescriptorBufferInfo, 3> &buf_infos);

void descriptor_sets_update(const uint32_t &idx, const descriptor_set &set, const device &dev, const uniform_buffer &buf, const std::vector<shader_storage_buffer> &ssbos);

void descriptor_sets_create(std::vector<descriptor_set> *sets, const device &dev, const descriptor_pool &pool, const descriptor_set_layout &set_lyt, const std::vector<uniform_buffer> &bufs, const std::vector<shader_storage_buffer> &ssbos);

#endif
