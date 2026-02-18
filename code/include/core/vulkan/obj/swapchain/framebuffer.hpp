#ifndef MOD_FRAMEBUFFER_HPP
#define MOD_FRAMEBUFFER_HPP

#include <vulkan/vulkan.h>

struct swapchain_state;
struct device;
struct render_pass;

VkFramebufferCreateInfo framebuffer_create_info(const swapchain_state &st, const render_pass &rp, const VkImageView &atts);

void framebuffers_create(swapchain_state *st, const device &dev, const render_pass &rp);

void framebuffers_destroy(const swapchain_state &st, const device &dev);

#endif
