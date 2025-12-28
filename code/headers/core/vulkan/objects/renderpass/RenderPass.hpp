#pragma once

#include "core/vulkan/objects/swapchain/Swapchain.hpp"

#include <vulkan/vulkan.h>

struct RenderPass {
    VkRenderPass handle = VK_NULL_HANDLE;
};

VkRenderPassBeginInfo render_pass_create_begin_info(const RenderPass &render_pass, const Swapchain &swapchain, uint32_t img_idx, const VkClearValue clear_color);

VkAttachmentDescription render_pass_create_attachment_description(const Swapchain& swapchain);

VkAttachmentReference render_pass_create_attachment_reference();

VkSubpassDescription render_pass_create_subpass_description(VkAttachmentReference* pattachment_ref);

VkSubpassDependency render_pass_create_subpass_dependency();

VkRenderPassCreateInfo render_pass_create_info(VkAttachmentDescription* pattachemnt_description, VkSubpassDescription* psubpass, VkSubpassDependency* subpass_dependency);

void render_pass_create(RenderPass* render_pass, const LogicalDevice& device, const Swapchain& swapchain);
    
void render_pass_destroy(RenderPass* render_pass, const LogicalDevice& device);
