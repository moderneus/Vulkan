#include "core/vulkan/objects/RenderPass.hpp"
#include "util/debug/Logger.hpp"

VkRenderPassBeginInfo render_pass_create_begin_info(const RenderPass &render_pass, const Swapchain &swapchain, uint32_t img_idx) {
    VkRenderPassBeginInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    create_info.renderPass = render_pass.handle;
    create_info.framebuffer = swapchain.frame_buffers[img_idx];
    create_info.renderArea.offset = {0, 0};
    create_info.renderArea.extent = swapchain.extent;
    VkClearValue clear_color = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
    create_info.clearValueCount = 1;
    create_info.pClearValues = &clear_color;
    return create_info;
}

VkAttachmentDescription render_pass_create_attachment_description(const Swapchain& swapchain) {
    log_info("Creating an Attachment Description...");
    VkAttachmentDescription description = {};
    description.format = swapchain.format;
    description.samples = VK_SAMPLE_COUNT_1_BIT;
    description.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    description.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    description.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    log_success("The Attachment Description was Created!");
    return description;
}

VkAttachmentReference render_pass_create_attachment_reference() {
    log_info("Creating the Attachment Reference...");
    VkAttachmentReference ref = {};
    ref.attachment = 0;
    ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    log_success("The Attachment Reference was Created!");
    return ref;
}

VkSubpassDescription render_pass_create_subpass_description(VkAttachmentReference* pattachment_ref) {
    log_info("Creating a Subpass Description...");
    VkSubpassDescription description = {};
    description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    description.colorAttachmentCount = 1;
    description.pColorAttachments = pattachment_ref;
    log_success("The Subpasss Description was Created!");
    return description;
}

VkSubpassDependency render_pass_create_subpass_dependency() {
    VkSubpassDependency dependency = {};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    return dependency;
}

VkRenderPassCreateInfo render_pass_create_info(VkAttachmentDescription* pattachemnt_description, VkSubpassDescription* psubpass, VkSubpassDependency* subpass_dependency) {
    log_info("Creating the Render Pass Info...");
    VkRenderPassCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    create_info.attachmentCount = 1;
    create_info.pAttachments = pattachemnt_description;
    create_info.subpassCount = 1;
    create_info.pSubpasses = psubpass;
    create_info.dependencyCount = 1;
    create_info.pDependencies = subpass_dependency;
    log_success("The Render Pass Info was Created!");
    return create_info;
}

void render_pass_create(RenderPass* render_pass, const LogicalDevice& device, const Swapchain& swapchain) {
    log_info("Creating a Render Pass...");
    VkAttachmentDescription color_attachment = render_pass_create_attachment_description(swapchain);
    VkAttachmentReference color_attachment_ref = render_pass_create_attachment_reference();
    VkSubpassDescription subpass = render_pass_create_subpass_description(&color_attachment_ref);
    VkSubpassDependency subpass_dependency = render_pass_create_subpass_dependency();
    VkRenderPassCreateInfo render_pass_info = render_pass_create_info(&color_attachment, &subpass, &subpass_dependency);
    if(vkCreateRenderPass(device.handle, &render_pass_info, nullptr, &render_pass->handle) != VK_SUCCESS) {
        log_critical("Failed to Create the Render Pass!");
    }
    log_success("The Render Pass was Created!");
}

void render_pass_destroy(RenderPass* render_pass, const LogicalDevice& device) {
    log_info("Destroying the Render Pass...");
    if(render_pass->handle == VK_NULL_HANDLE) {
        log_error("Cannot Destroy the Render Pass::Render Pass is not Created!");
    }
    vkDestroyRenderPass(device.handle, render_pass->handle, nullptr);
    log_success("The Render Pass was Destroyed!");
}
