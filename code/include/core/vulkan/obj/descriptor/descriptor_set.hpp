#ifndef MOD_DESCRIPTOR_SET_HPP
#define MOD_DESCRIPTOR_SET_HPP

#include <vulkan/vulkan.h>

#include <vector>

struct device;
struct descriptor_set_layout;
struct descriptor_pool;
struct uniform_buffer;

struct descriptor_set {
	VkDescriptorSet handle = VK_NULL_HANDLE;
};

VkDescriptorSetAllocateInfo descriptor_set_create_alloc_info(const std::vector<VkDescriptorSetLayout> &set_lyts, const descriptor_pool &pool);

VkDescriptorBufferInfo descriptor_set_create_buf_info(const uniform_buffer &buf);

VkWriteDescriptorSet descriptor_set_create_write_info(const descriptor_set &set, VkDescriptorBufferInfo buf_info);

void descriptor_sets_update(const descriptor_set &set, const uniform_buffer &buf, const device &dev);

void descriptor_sets_create(std::vector<descriptor_set> *sets, const device &dev, const descriptor_pool &pool, const descriptor_set_layout &set_lyt, const std::vector<uniform_buffer> &bufs);

#endif
