#ifndef MOD_IMAGE_VIEW_HPP
#define MOD_IMAGE_VIEW_HPP

#include <vulkan/vulkan.h>

struct device;
struct swapchain_state;

VkImageViewCreateInfo image_view_create_info(const VkImage &img, const VkFormat &fmt);

void image_views_create(swapchain_state *st, const device &dev);

void image_views_destroy(const swapchain_state &st, const device &dev);

#endif
