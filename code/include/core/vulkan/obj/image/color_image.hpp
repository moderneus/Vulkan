#ifndef MOD_COLOR_IMAGE_HPP
#define MOD_COLOR_IMAGE_HPP

#include "core/vulkan/obj/image/image.hpp"
#include "core/vulkan/obj/image/image_view.hpp"

struct swapchain_state;

struct color_image {
	image img;
	image_view view;
};

void color_image_create(swapchain_state *st, const device &dev, const physical_device &gpu);

void color_image_destroy(const swapchain_state &st, const device &dev);

#endif
