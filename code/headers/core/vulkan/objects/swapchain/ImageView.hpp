#ifndef MOD_IMAGE_VIEW_HPP
#define MOD_IMAGE_VIEW_HPP

#include <vulkan/vulkan.h>

struct device_t;
struct swapchain_config_t;

VkImageViewCreateInfo img_view_create_info(const VkImage& img, const VkFormat& format);

void img_views_create(swapchain_config_t* cfg, const device_t& device);

void img_views_destroy(const swapchain_config_t& cfg, const device_t& device);

#endif
