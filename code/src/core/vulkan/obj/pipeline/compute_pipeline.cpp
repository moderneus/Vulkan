#include "core/vulkan/obj/pipeline/compute_pipeline.hpp"
#include "core/vulkan/obj/pipeline/pipeline_layout.hpp"
#include "core/vulkan/obj/pipeline/pipeline.hpp"
#include "core/vulkan/obj/pipeline/shader.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "util/debug/log.hpp"

VkPipelineShaderStageCreateInfo compute_pipeline_create_shdr_stage_info(const shader &shdr)
{
	VkPipelineShaderStageCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	info.stage = VK_SHADER_STAGE_COMPUTE_BIT;
	info.module = shdr.handle;
	info.pName = "main";
	return info;
}

VkComputePipelineCreateInfo compute_pipeline_create_info(const pipeline_layout &lyt, const VkPipelineShaderStageCreateInfo &shdr_info)
{
	VkComputePipelineCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
	info.layout = lyt.handle;
	info.stage = shdr_info;
	return info;
}

void compute_pipeline_create(pipeline *pl, const device &dev, const pipeline_layout &lyt, const shader &shdr)
{
	VkPipelineShaderStageCreateInfo shdr_info = compute_pipeline_create_shdr_stage_info(shdr);
	VkComputePipelineCreateInfo info = compute_pipeline_create_info(lyt, shdr_info);

	if (vkCreateComputePipelines(dev.handle, VK_NULL_HANDLE, 1, &info, nullptr, &pl->handle))
		log_critical("Failed to Create the Compute Pipeline.");
}

void compute_pipeline_destroy(const pipeline &pl, const device &dev)
{
	log_info("Destroying the Compute Pipeline...");

	if (pl.handle == VK_NULL_HANDLE)
		log_error("Cannot Destroy the Compute Pipeline::Compute Pipeline is not Created.");

	vkDestroyPipeline(dev.handle, pl.handle, nullptr);

	log_info("The Compute Pipeline was Destroyed.");
}
