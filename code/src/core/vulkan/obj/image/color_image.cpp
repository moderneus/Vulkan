#include "core/vulkan/obj/image/color_image.hpp"
#include "core/vulkan/obj/swapchain/swapchain.hpp"
#include "core/vulkan/obj/device/physical_device.hpp"

void color_image_create(swapchain_state *st, const device &dev, const physical_device &gpu)
{
	st->col_img.img.extent.width = st->imgs[0].extent.width;
	st->col_img.img.extent.height = st->imgs[0].extent.height;
	st->col_img.img.tiling = st->imgs[0].tiling;
	st->col_img.img.mip_lvls = 1;
	st->col_img.img.fmt = st->imgs[0].fmt;
	st->col_img.img.usage = VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	st->col_img.img.samples = physical_device_get_max_usable_sample_cnt(gpu);
	st->col_img.img.aspect_flags = VK_IMAGE_ASPECT_COLOR_BIT;

	image_create(&st->col_img.img, dev, gpu, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	image_view_create(&st->col_img.view, dev, st->col_img.img);
}

void color_image_destroy(const swapchain_state &st, const device &dev)
{
	image_destroy(st.col_img.img, dev);
	image_view_destroy(st.col_img.view, dev);
}
