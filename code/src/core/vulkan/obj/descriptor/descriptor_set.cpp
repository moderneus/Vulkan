#include "core/vulkan/obj/descriptor/descriptor_set.hpp"
#include "core/vulkan/obj/descriptor/descriptor_pool.hpp"
#include "core/vulkan/obj/descriptor/descriptor_set_layout.hpp"
#include "core/vulkan/obj/buffer/shader_storage_buffer.hpp"
#include "core/vulkan/obj/buffer/uniform_buffer.hpp"
#include "core/vulkan/obj/image/image_view.hpp"
#include "core/vulkan/obj/image/sampler.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "util/constants.hpp"
#include "util/debug/log.hpp"

VkDescriptorSetAllocateInfo descriptor_set_create_alloc_info(const std::vector<VkDescriptorSetLayout> &set_lyts, const descriptor_pool &pool)
{
	log_info("Creating the Descriptor Set Allocation Info...");

	VkDescriptorSetAllocateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	info.descriptorPool = pool.handle;
	info.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
	info.pSetLayouts = set_lyts.data();

	log_info("The Descriptor Set Allocation Info was Created.");

	return info;
}

std::array<VkDescriptorBufferInfo, 3> descriptor_set_create_bufs_info(const uint32_t &idx, const uniform_buffer &buf, const std::vector<shader_storage_buffer> &ssbos)
{
	log_info("Creating the Descriptor Set Buffer Info...");

	std::array<VkDescriptorBufferInfo, 3> infos = {};
	infos[0].buffer = buf.ubuf.handle;
	infos[0].offset = 0;
	infos[0].range = sizeof(uniform_buffer) - sizeof(buffer);

	infos[1].buffer = ssbos[(idx + MAX_FRAMES_IN_FLIGHT - 1) % MAX_FRAMES_IN_FLIGHT].sbuf.handle;
	infos[1].offset = 0;
	infos[1].range = sizeof(vertex) * PARTICLE_COUNT;

	infos[2].buffer = ssbos[idx].sbuf.handle;
	infos[2].offset = 0;
	infos[2].range = sizeof(vertex) * PARTICLE_COUNT;

	log_info("The Descriptor Set Buffer Info was Created.");

	return infos;
}

VkDescriptorImageInfo descriptor_set_create_img_info(const image_view &view, const sampler &samp)
{
	VkDescriptorImageInfo info = {};
	info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	info.imageView = view.handle;
	info.sampler = samp.handle;
	return info;
}

std::array<VkWriteDescriptorSet, 3> descriptor_set_create_write_infos(const descriptor_set &set, const std::array<VkDescriptorBufferInfo, 3> &buf_infos)
{
	log_info("Creating the Descriptor Set Write Info...");

	std::array<VkWriteDescriptorSet, 3> infos = {};

	infos[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	infos[0].dstSet = set.handle;
	infos[0].dstBinding = 0;
	infos[0].dstArrayElement = 0;
	infos[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	infos[0].descriptorCount = 1;
	infos[0].pBufferInfo = &buf_infos[0];

	infos[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	infos[1].dstSet = set.handle;
	infos[1].dstBinding = 1;
	infos[1].dstArrayElement = 0;
	infos[1].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	infos[1].descriptorCount = 1;
	infos[1].pBufferInfo = &buf_infos[1];

	infos[2].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	infos[2].dstSet = set.handle;
	infos[2].dstBinding = 2;
	infos[2].dstArrayElement = 0;
	infos[2].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	infos[2].descriptorCount = 1;
	infos[2].pBufferInfo = &buf_infos[2];

	log_info("The Descriptor Set Write Info was Created.");

	return infos; 
}

void descriptor_sets_update(const uint32_t &idx, const descriptor_set &set, const device &dev, const uniform_buffer &buf, const std::vector<shader_storage_buffer> &ssbos)
{
	log_info("Updating the Descriptor Sets...");

	std::array<VkDescriptorBufferInfo, 3> buf_infos = descriptor_set_create_bufs_info(idx, buf, ssbos);
	std::array<VkWriteDescriptorSet, 3> write_infos = descriptor_set_create_write_infos(set, buf_infos);

	vkUpdateDescriptorSets(dev.handle, static_cast<uint32_t>(write_infos.size()), write_infos.data(), 0, nullptr);

	log_info("The Descriptor Sets were Updated.");
}

void descriptor_sets_create(std::vector<descriptor_set> *sets, const device &dev, const descriptor_pool &pool, const descriptor_set_layout &set_lyt, const std::vector<uniform_buffer> &bufs, const std::vector<shader_storage_buffer> &ssbos)
{
	log_info("Creating the Descriptor Sets...");

	std::vector<VkDescriptorSetLayout> set_lyts(MAX_FRAMES_IN_FLIGHT, set_lyt.handle);
	VkDescriptorSetAllocateInfo info = descriptor_set_create_alloc_info(set_lyts, pool);

	sets->resize(MAX_FRAMES_IN_FLIGHT);
	if (vkAllocateDescriptorSets(dev.handle, &info, &sets->data()->handle) != VK_SUCCESS)
		log_critical("Failed to Allocate the Descriptor Sets.");

	for(uint32_t i = 0; i < sets->size(); ++i)
		descriptor_sets_update(i, sets->data()[i], dev, bufs[i], ssbos);

	log_info("The Descriptor Sets were Created.");
}
