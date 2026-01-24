#ifndef MOD_FRAMEBUFFER_HPP
#define MOD_FRAMEBUFFER_HPP

#include <vulkan/vulkan.h>

struct swapchain_t;
struct device_t;
struct render_pass_t;

VkFramebufferCreateInfo framebuffer_create_info(const swapchain_t& swapchain, const render_pass_t& render_pass, const VkImageView* attachments);

void framebuffer_create(swapchain_t* swapchain, const device_t& device, const render_pass_t& render_pass);

void framebuffer_destroy(const swapchain_t& swapchain, const device_t& device);

#endif
