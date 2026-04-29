#ifndef MOD_FRAMEBUFFER_HPP
#define MOD_FRAMEBUFFER_HPP

#include <vulkan/vulkan.h>

#include <array>

struct swapchain_state;
struct depth_image;
struct device;
struct render_pass;

VkFramebufferCreateInfo framebuffer_create_info(const swapchain_state &st, const render_pass &rp, const std::array<VkImageView, 1> &atts);

void framebuffers_create(swapchain_state *st, const device &dev, const render_pass &rp);

void framebuffers_destroy(const swapchain_state &st, const device &dev);

#endif
