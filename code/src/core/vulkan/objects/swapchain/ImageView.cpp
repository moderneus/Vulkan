#include "core/vulkan/objects/swapchain/ImageView.hpp"
#include "core/vulkan/objects/swapchain/Swapchain.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "util/debug/Logger.hpp"

VkImageViewCreateInfo img_view_create_info(const VkImage &img, const VkFormat &format) 
{
	VkImageViewCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	info.image = img;
	info.viewType = VK_IMAGE_VIEW_TYPE_2D;
	info.format = format;
	info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
	info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
	info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
	info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
	info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	info.subresourceRange.baseMipLevel = 0;
	info.subresourceRange.levelCount = 1;
	info.subresourceRange.baseArrayLayer = 0;
	info.subresourceRange.layerCount = 1;
	return info;
}

void img_views_create(swapchain_state_t *st, const device_t &dev) 
{
	log_info("Creating an Image Views...");

	st->views.resize(st->imgs.size());

	for(uint32_t i = 0; i < st->imgs.size(); ++i) {
		VkImageViewCreateInfo info = img_view_create_info(st->imgs[i], st->format);

		if (vkCreateImageView(dev.handle, &info, nullptr, &st->views[i]) != VK_SUCCESS) {
			log_critical("Failed to Create the ImageView.");
		}
	}

	log_info("The Image Views were Created.");
}

void img_views_destroy(const swapchain_state_t &st, const device_t &dev) 
{
	log_info("Destroying the Image Views...");

	for(auto& view : st.views) {
		vkDestroyImageView(dev.handle, view, nullptr);
	}

	log_info("The Image Views were Destroyed.");
}
