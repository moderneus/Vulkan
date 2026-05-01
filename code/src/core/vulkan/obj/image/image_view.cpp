#include "core/vulkan/obj/image/image_view.hpp"
#include "core/vulkan/obj/swapchain/swapchain.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "core/vulkan/obj/image/image.hpp"
#include "util/debug/log.hpp"

VkImageViewCreateInfo image_view_create_info(const image &img) 
{
	VkImageViewCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	info.image = img.handle;
	info.viewType = VK_IMAGE_VIEW_TYPE_2D;
	info.format = img.fmt;
	info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
	info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
	info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
	info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
	info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	info.subresourceRange.baseMipLevel = 0;
	info.subresourceRange.levelCount = img.mip_lvls;
	info.subresourceRange.baseArrayLayer = 0;
	info.subresourceRange.layerCount = 1;
	info.subresourceRange.aspectMask = img.aspect_flags;
	return info;
}

void image_view_create(image_view *view, const device &dev, const image &img)
{
	log_info("Creating an Image View...");

	VkImageViewCreateInfo info = image_view_create_info(img);

	if (vkCreateImageView(dev.handle, &info, nullptr, &view->handle) != VK_SUCCESS)
		log_critical("Failed to Create the ImageView.");

	log_info("The Image View was Created.");
}

void image_views_create(swapchain_state *st, const device &dev) 
{
	log_info("Creating an Image Views...");

	st->views.resize(st->imgs.size());

	for(uint32_t i = 0; i < st->imgs.size(); ++i)
		image_view_create(&st->views.data()[i], dev, st->imgs[i]);

	log_info("The Image Views were Created.");
}

void image_view_destroy(const image_view &view, const device &dev)
{
	if (view.handle == VK_NULL_HANDLE)
		log_info("Cannot Destroy the Image View::Image View is not Created.");

	vkDestroyImageView(dev.handle, view.handle, nullptr);
}

void image_views_destroy(const swapchain_state &st, const device &dev) 
{
	log_info("Destroying the Image Views...");

	for(auto &view : st.views)
		image_view_destroy(view, dev);

	log_info("The Image Views were Destroyed.");
}
