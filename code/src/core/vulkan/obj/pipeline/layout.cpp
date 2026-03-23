#include "core/vulkan/obj/pipeline/layout.hpp"
#include "core/vulkan/obj/descriptor/set_layout.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "util/debug/log.hpp"

#include <vulkan/vulkan.h>

VkPipelineLayoutCreateInfo layout_create_info(const descriptor_set_layout &set_lyt)
{
	log_info("Creating the Pipeline Layout Info...");
	
	VkPipelineLayoutCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	info.setLayoutCount = 1;
	info.pSetLayouts = &set_lyt.handle;
	log_info("The Pipeline Layout Info was Created.");

	return info;
}


void layout_create(layout *lyt, const device &dev, const descriptor_set_layout &set_lyt)
{
	log_info("Creating a Pipeline Layout...");

	VkPipelineLayoutCreateInfo info = layout_create_info(set_lyt);

	if (vkCreatePipelineLayout(dev.handle, &info, nullptr, &lyt->handle) != VK_SUCCESS)
		log_critical("Failed to Create the Pipeline Layout.");

	log_info("The Pipeline Layout was Created.");
}

void layout_destroy(const layout &lyt, const device &dev) 
{
	log_info("Destroying the Pipeline Layout...");

	if (lyt.handle == VK_NULL_HANDLE)
		log_error("Cannot Destroy the Pipeline Layout::Pipeline Layout is not Created.");

	vkDestroyPipelineLayout(dev.handle, lyt.handle, nullptr);

	log_info("The Pipeline Layout was Destroyed.");
}
