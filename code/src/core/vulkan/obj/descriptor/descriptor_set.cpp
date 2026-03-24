#include "core/vulkan/obj/descriptor/descriptor_set.hpp"
#include "core/vulkan/obj/descriptor/descriptor_pool.hpp"
#include "core/vulkan/obj/descriptor/descriptor_set_layout.hpp"
#include "core/vulkan/obj/buffer/uniform_buffer.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "util/constants.hpp"
#include "util/debug/log.hpp"

VkDescriptorSetAllocateInfo descriptor_set_create_alloc_info(const std::vector<VkDescriptorSetLayout> &set_lyts, const descriptor_pool &pool)
{
	VkDescriptorSetAllocateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	info.descriptorPool = pool.handle;
	info.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
	info.pSetLayouts = set_lyts.data();
	return info;
}

VkDescriptorBufferInfo descriptor_set_create_buf_info(const uniform_buffer &buf)
{
	VkDescriptorBufferInfo info = {};
	info.buffer = buf.ubuf.handle;
	info.offset = 0;
	info.range = sizeof(uniform_buffer) - sizeof(buffer);
	return info;
}

VkWriteDescriptorSet descriptor_set_create_write_info(const descriptor_set &set, VkDescriptorBufferInfo buf_info)
{
	VkWriteDescriptorSet info = {};
	info.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	info.dstSet = set.handle;
	info.dstBinding = 0;
	info.dstArrayElement = 0;
	info.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	info.descriptorCount = 1;
	info.pBufferInfo = &buf_info;
	return info; 
}

void descriptor_sets_update(const descriptor_set &set, const uniform_buffer &buf, const device &dev)
{
	VkDescriptorBufferInfo buf_info = descriptor_set_create_buf_info(buf);
	VkWriteDescriptorSet write_info = descriptor_set_create_write_info(set, buf_info);

	vkUpdateDescriptorSets(dev.handle, 1, &write_info, 0, nullptr);
}

void descriptor_sets_create(std::vector<descriptor_set> *sets, const device &dev, const descriptor_pool &pool, const descriptor_set_layout &set_lyt, const std::vector<uniform_buffer> &bufs)
{
	std::vector<VkDescriptorSetLayout> set_lyts(MAX_FRAMES_IN_FLIGHT, set_lyt.handle);
	VkDescriptorSetAllocateInfo info = descriptor_set_create_alloc_info(set_lyts, pool);

	sets->resize(MAX_FRAMES_IN_FLIGHT);
	if (vkAllocateDescriptorSets(dev.handle, &info, &sets->data()->handle) != VK_SUCCESS)
		log_critical("Failed to Allocate the Descriptor Sets.");

	for(uint32_t i = 0; i < sets->size(); ++i)
		descriptor_sets_update(sets->data()[i], bufs[i], dev);
}
