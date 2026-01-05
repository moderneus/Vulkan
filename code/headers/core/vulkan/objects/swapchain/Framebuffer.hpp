#pragma once

#include <vulkan/vulkan.h>

struct Swapchain;
struct LogicalDevice;
struct RenderPass;

VkFramebufferCreateInfo framebuffer_create_info(const Swapchain& swapchain, const RenderPass& render_pass, const VkImageView* attachments);

void framebuffer_create(Swapchain* swapchain, const LogicalDevice& device, const RenderPass& render_pass);

void framebuffer_destroy(const Swapchain& swapchain, const LogicalDevice& device);
