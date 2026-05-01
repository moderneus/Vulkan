#ifndef MOD_SAMPLER_HPP
#define MOD_SAMPLER_HPP

#include <vulkan/vulkan.h>

struct physical_device;
struct device;

struct sampler {
	VkSampler handle = VK_NULL_HANDLE;
};

void sampler_create(sampler *samp, const device &dev, const physical_device &gpu);

void sampler_destroy(const sampler &samp, const device &dev);

#endif
