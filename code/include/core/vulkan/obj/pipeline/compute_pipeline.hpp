#ifndef MOD_COMPUTE_PIPELINE_HPP
#define MOD_COMPUTE_PIPELINE_HPP

struct pipeline_layout;
struct shader;
struct pipeline;
struct device;

#include <vulkan/vulkan.h>

VkPipelineShaderStageCreateInfo compute_pipeline_create_shdr_stage_info(const shader &shdr);

VkComputePipelineCreateInfo compute_pipeline_create_info(const pipeline_layout &lyt, const VkPipelineShaderStageCreateInfo &shdr_info);

void compute_pipeline_create(pipeline *pl, const device &dev, const pipeline_layout &lyt, const shader &shdr);

void compute_pipeline_destroy(const pipeline &pl, const device &dev);

#endif
