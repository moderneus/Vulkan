#ifndef MOD_FRAMEBUFFER_HPP
#define MOD_FRAMEBUFFER_HPP

#include <vulkan/vulkan.h>

struct swapchain_config_t;
struct device_t;
struct render_pass_t;

VkFramebufferCreateInfo framebuffer_create_info(const swapchain_config_t& cfg, const render_pass_t& render_pass, const VkImageView* attachments);

void framebuffers_create(swapchain_config_t* cfg, const device_t& device, const render_pass_t& render_pass);

void framebuffers_destroy(const swapchain_config_t& cfg, const device_t& device);

#endif
