#include "core/vulkan/obj/image/sampler.hpp"
#include "core/vulkan/obj/device/physical_device.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "util/debug/log.hpp"

VkSamplerCreateInfo sampler_create_info(const VkPhysicalDeviceProperties &props)
{
	VkSamplerCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	info.magFilter = VK_FILTER_LINEAR;
	info.minFilter = VK_FILTER_LINEAR;
	info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	info.anisotropyEnable = VK_TRUE;
	info.maxAnisotropy = props.limits.maxSamplerAnisotropy;
	info.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
	info.unnormalizedCoordinates = VK_FALSE;
	info.compareEnable = VK_FALSE;
	info.compareOp = VK_COMPARE_OP_ALWAYS;
	info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	info.mipLodBias = 0.0f;
	info.minLod = 0.0f;
	info.maxLod = 0.0f;
	return info;
}

void sampler_create(sampler *samp, const device &dev, const physical_device &gpu)
{
	VkPhysicalDeviceProperties props = {};
	vkGetPhysicalDeviceProperties(gpu.handle, &props);

	VkSamplerCreateInfo info = sampler_create_info(props);

	if (vkCreateSampler(dev.handle, &info, nullptr, &samp->handle) != VK_SUCCESS)
		log_critical("Failed to Create the Sampler.");
}

void sampler_destroy(const sampler &samp, const device &dev)
{
	if (samp.handle == VK_NULL_HANDLE)
		log_error("Cannot Destroy the Sampler::Sampler is not Created.");

	vkDestroySampler(dev.handle, samp.handle, nullptr);
}
