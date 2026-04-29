#include "core/vulkan/obj/pipeline/compute_pipeline_layout.hpp"
#include "core/vulkan/obj/descriptor/descriptor_set_layout.hpp"
#include "core/vulkan/obj/pipeline/pipeline_layout.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "util/debug/log.hpp"

VkPipelineLayoutCreateInfo compute_pipeline_layout_create_info(const descriptor_set_layout &set_lyt)
{
	log_info("Creating the Compute Pipeline Layout Info...");
	
	VkPipelineLayoutCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	info.setLayoutCount = 1;
	info.pSetLayouts = &set_lyt.handle;

	log_info("The Compute Pipeline Layout Info was Created.");

	return info;
}

void compute_pipeline_layout_create(pipeline_layout *lyt, const device &dev, const descriptor_set_layout &set_lyt)
{
	log_info("Creating a Compute Pipeline Layout...");

	VkPipelineLayoutCreateInfo info = compute_pipeline_layout_create_info(set_lyt);

	if (vkCreatePipelineLayout(dev.handle, &info, nullptr, &lyt->handle) != VK_SUCCESS)
		log_critical("Failed to Create the Compute Pipeline Layout.");

	log_info("The Compute Pipeline Layout was Created.");
}

void compute_pipeline_layout_destroy(const pipeline_layout &lyt, const device &dev) 
{
	log_info("Destroying the Compute Pipeline Layout...");

	if (lyt.handle == VK_NULL_HANDLE)
		log_error("Cannot Destroy the Compute Pipeline Layout::Compute Pipeline Layout is not Created.");

	vkDestroyPipelineLayout(dev.handle, lyt.handle, nullptr);

	log_info("The Compute Pipeline Layout was Destroyed.");
}
