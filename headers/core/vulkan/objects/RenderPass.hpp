#pragma once

#include "core/vulkan/objects/ImageView.hpp"

#include <vulkan/vulkan.h>

struct RenderPass {
    VkRenderPass handle = VK_NULL_HANDLE;
};

VkAttachmentDescription render_pass_create_attachment_description(const ImageView& image_view);

VkAttachmentReference render_pass_create_attachment_reference();

VkSubpassDescription render_pass_create_subpass_description();

VkRenderPassCreateInfo render_pass_create_info();

void render_pass_create(RenderPass* render_pass, const LogicalDevice& device, const ImageView& image_view);
    
void render_pass_destroy(RenderPass* render_pass, const LogicalDevice& device);
