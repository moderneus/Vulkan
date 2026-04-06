#ifndef MOD_IMAGE_VIEW_HPP
#define MOD_IMAGE_VIEW_HPP

#include <vulkan/vulkan.h>

struct device;
struct swapchain_state;
struct image;

struct image_view {
	VkImageView handle = VK_NULL_HANDLE;
};

VkImageViewCreateInfo image_view_create_info(const VkImage &img);

void image_view_create(image_view *view, const device &dev, const image &img);

void image_views_create(swapchain_state *st, const device &dev);

void image_view_destroy(const image_view &view, const device &dev);

void image_views_destroy(const swapchain_state &st, const device &dev);

#endif
