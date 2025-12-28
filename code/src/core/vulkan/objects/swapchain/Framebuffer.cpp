#include "core/vulkan/objects/swapchain/Framebuffer.hpp"
#include "util/debug/Logger.hpp"

VkFramebufferCreateInfo framebuffer_create_info(const Swapchain& swapchain, const RenderPass& render_pass, const VkImageView* attachments) {
    VkFramebufferCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    create_info.renderPass = render_pass.handle;
    create_info.attachmentCount = 1;
    create_info.pAttachments = attachments;
    create_info.width = swapchain.extent.width;
    create_info.height = swapchain.extent.height;
    create_info.layers = 1;
    return create_info;
}

void framebuffer_create(Swapchain* swapchain, const LogicalDevice& device, const RenderPass& render_pass) {
    log_info("Creating a Framebuffers...");
    swapchain->frame_buffers.resize(swapchain->views.size());
    for(uint32_t i = 0; i < swapchain->views.size(); ++i) {
        VkImageView attachments[] = {swapchain->views[i]};
        VkFramebufferCreateInfo framebuffer_info = framebuffer_create_info(*swapchain, render_pass, attachments);
        if(vkCreateFramebuffer(device.handle, &framebuffer_info, nullptr, &swapchain->frame_buffers[i]) != VK_SUCCESS) {
            log_critical("Failed to Create the Framebuffers!");
        }
    }
    log_success("The Framebuffers were Created!");
}

void framebuffer_destroy(const Swapchain& swapchain, const LogicalDevice& device) {
    log_info("Destroying the Framebuffers...");
    for(auto& framebuffer : swapchain.frame_buffers) {
        vkDestroyFramebuffer(device.handle, framebuffer, nullptr);
    }
    log_success("The Framebuffers were Destroyed!");
}
