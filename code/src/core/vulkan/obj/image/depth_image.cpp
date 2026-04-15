#include "core/vulkan/obj/image/depth_image.hpp"
#include "core/vulkan/obj/device/physical_device.hpp"
#include "core/vulkan/obj/swapchain/swapchain.hpp"

VkFormat depth_image_find_fmt(const physical_device &gpu)
{
	return physical_device_find_supp_fmt
	(
		gpu,
		{VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
		VK_IMAGE_TILING_OPTIMAL,
		VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
	);
}

void depth_image_create(depth_image *dp_img, const device &dev, const physical_device &gpu, const swapchain_state &st)
{
	VkFormat fmt = depth_image_find_fmt(gpu);

	dp_img->img.extent.width = st.imgs[0].extent.width;
	dp_img->img.extent.height = st.imgs[0].extent.height;
	dp_img->img.fmt = fmt;
	dp_img->img.tiling = VK_IMAGE_TILING_OPTIMAL;
	dp_img->img.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
	dp_img->img.aspect_flags = VK_IMAGE_ASPECT_DEPTH_BIT;

	image_create(&dp_img->img, dev, gpu, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	image_view_create(&dp_img->view, dev, dp_img->img);
}

void depth_image_destroy(const depth_image &dp_img, const device &dev)
{
	image_destroy(dp_img.img, dev);
	image_view_destroy(dp_img.view, dev);
}
