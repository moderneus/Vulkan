#ifndef MOD_IMAGE_VIEW_HPP
#define MOD_IMAGE_VIEW_HPP

#include <vulkan/vulkan.h>

struct device_t;
struct swapchain_state_t;

VkImageViewCreateInfo img_view_create_info(const VkImage &img, const VkFormat &format);

void img_views_create(swapchain_state_t *st, const device_t &dev);

void img_views_destroy(const swapchain_state_t &st, const device_t &dev);

#endif
