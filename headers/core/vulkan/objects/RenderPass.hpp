#pragma once

#include "core/vulkan/objects/Swapchain.hpp"

#include <vulkan/vulkan.h>

struct RenderPass {
    VkRenderPass handle = VK_NULL_HANDLE;
};

VkRenderPassBeginInfo render_pass_create_begin_info(const RenderPass &render_pass, const Swapchain &swapchain, uint32_t img_idx);

VkAttachmentDescription render_pass_create_attachment_description(const Swapchain& swapchain);

VkAttachmentReference render_pass_create_attachment_reference();

VkSubpassDescription render_pass_create_subpass_description();

VkRenderPassCreateInfo render_pass_create_info();

void render_pass_create(RenderPass* render_pass, const LogicalDevice& device, const Swapchain& swapchain);
    
void render_pass_destroy(RenderPass* render_pass, const LogicalDevice& device);
