#include "core/vulkan/objects/Swapchain.hpp"
#include "core/vulkan/objects/LogicalDevice.hpp"
#include "core/vulkan/objects/RenderPass.hpp"

VkFramebufferCreateInfo framebuffer_create_info(const Swapchain& swapchain, const RenderPass& render_pass, const VkImageView* attachments);

void framebuffer_create(Swapchain* swapchain, const LogicalDevice& device, const RenderPass& render_pass);

void framebuffer_destroy(const Swapchain& swapchain, const LogicalDevice& device);
