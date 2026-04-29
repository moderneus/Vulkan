#ifndef MOD_COMPUTE_PIPELINE_LAYOUT_HPP
#define MOD_COMPUTE_PIPELINE_LAYOUT_HPP

#include <vulkan/vulkan.h>

struct descriptor_set_layout;
struct pipeline_layout;
struct device;

VkPipelineLayoutCreateInfo compute_pipeline_layout_create_info(const descriptor_set_layout &set_lyt);

void compute_pipeline_layout_create(pipeline_layout *lyt, const device &dev, const descriptor_set_layout &set_lyt);

void compute_pipeline_layout_destroy(const pipeline_layout &lyt, const device &dev);

#endif
