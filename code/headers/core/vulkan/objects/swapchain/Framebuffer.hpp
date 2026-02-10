#ifndef MOD_FRAMEBUFFER_HPP
#define MOD_FRAMEBUFFER_HPP

#include <vulkan/vulkan.h>

struct swapchain_state_t;
struct device_t;
struct render_pass_t;

VkFramebufferCreateInfo fb_create_info(const swapchain_state_t &st, const render_pass_t &rp, const VkImageView *atts);

void fbs_create(swapchain_state_t *st, const device_t &dev, const render_pass_t &rp);

void fbs_destroy(const swapchain_state_t &st, const device_t &dev);

#endif
