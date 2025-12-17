#include "core/vulkan/objects/PipelineLayout.hpp"
#include "util/debug/Logger.hpp"

#include <vulkan/vulkan.h>

VkPipelineLayoutCreateInfo pipeline_layout_create_info() {
    VkPipelineLayoutCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    create_info.setLayoutCount = 0;
    create_info.pSetLayouts = nullptr;
    create_info.pushConstantRangeCount = 0;
    return create_info;
}

void pipeline_layout_create(PipelineLayout* pipeline_layout, const LogicalDevice& device) {
    log_info("Creating a Pipeline Layout...");
    VkPipelineLayoutCreateInfo pipelineLayoutInfo = pipeline_layout_create_info();
    if(vkCreatePipelineLayout(device.handle, &pipelineLayoutInfo, nullptr, &pipeline_layout->handle) != VK_SUCCESS) {
        log_critical("Failed to Create the Pipeline Layout!");
    }
    log_success("The Pipeline Layout was Created!");
}

void pipeline_layout_destroy(const PipelineLayout& pipeline_layout, const LogicalDevice& device) {
    log_info("Destroying the Pipeline Layout...");
    if(pipeline_layout.handle == VK_NULL_HANDLE) {
        log_error("Cannot Destroy the Pipeline Layout::Pipeline Layout is not Created!");
    }
    vkDestroyPipelineLayout(device.handle, pipeline_layout.handle, nullptr);
    log_success("The Pipeline Layout was Destroyed!");
}
