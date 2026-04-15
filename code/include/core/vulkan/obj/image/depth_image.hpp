#ifndef MOD_DEPTH_IMAGE_HPP
#define MOD_DEPTH_IMAGE_HPP

#include "core/vulkan/obj/image/image.hpp"
#include "core/vulkan/obj/image/image_view.hpp"

struct physical_device;
struct swapchain_state;
struct device;

struct depth_image {
	image		img;
	image_view	view;
};

VkFormat depth_image_find_fmt(const physical_device &gpu);

void depth_image_create(depth_image *dp_img, const device &dev, const physical_device &gpu, const swapchain_state &st);

void depth_image_destroy(const depth_image &img, const device &dev);

#endif
