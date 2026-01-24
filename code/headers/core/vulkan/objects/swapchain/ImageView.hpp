#ifndef MOD_IMAGE_VIEW_HPP
#define MOD_IMAGE_VIEW_HPP

#include <vulkan/vulkan.h>

struct device_t;
struct swapchain_t;

VkImageViewCreateInfo img_view_create_info(const VkImage& img, const VkFormat& format);

void img_view_create(swapchain_t* swapchain, const device_t& device);

void img_view_destroy(const swapchain_t& swapchain, const device_t& device);

#endif
