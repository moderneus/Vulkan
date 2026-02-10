#include "core/vulkan/objects/pipeline/PipelineLayout.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "util/debug/Logger.hpp"

#include <vulkan/vulkan.h>

VkPipelineLayoutCreateInfo pipeline_layout_create_info() 
{
	log_info("Creating the Pipeline Layout Info...");
	
	VkPipelineLayoutCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	info.setLayoutCount = 0;
	info.pSetLayouts = nullptr;
	info.pushConstantRangeCount = 0;

	log_info("The Pipeline Layout Info was Created.");

	return info;
}

void pipeline_layout_create(pipeline_layout_t *layout, const device_t &dev) 
{
	log_info("Creating a Pipeline Layout...");

	VkPipelineLayoutCreateInfo info = pipeline_layout_create_info();

	if (vkCreatePipelineLayout(dev.handle, &info, nullptr, &layout->handle) != VK_SUCCESS) {
		log_critical("Failed to Create the Pipeline Layout.");
	}

	log_info("The Pipeline Layout was Created.");
}

void pipeline_layout_destroy(const pipeline_layout_t &layout, const device_t &dev) 
{
	log_info("Destroying the Pipeline Layout...");

	if (layout.handle == VK_NULL_HANDLE) {
		log_error("Cannot Destroy the Pipeline Layout::Pipeline Layout is not Created.");
	}

	vkDestroyPipelineLayout(dev.handle, layout.handle, nullptr);

	log_info("The Pipeline Layout was Destroyed.");
}
