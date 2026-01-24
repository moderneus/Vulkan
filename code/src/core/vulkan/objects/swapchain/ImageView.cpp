#include "core/vulkan/objects/swapchain/ImageView.hpp"
#include "core/vulkan/objects/swapchain/Swapchain.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "util/debug/Logger.hpp"

VkImageViewCreateInfo img_view_create_info(const VkImage& img, const VkFormat& format) 
{
	VkImageViewCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	create_info.image = img;
	create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
	create_info.format = format;
	create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
	create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
	create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
	create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
	create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	create_info.subresourceRange.baseMipLevel = 0;
	create_info.subresourceRange.levelCount = 1;
	create_info.subresourceRange.baseArrayLayer = 0;
	create_info.subresourceRange.layerCount = 1;
	return create_info;
}

void img_view_create(swapchain_t* swapchain, const device_t& device) 
{
	log_info("Creating an Image Views...");

	uint32_t image_count = 0;
	vkGetSwapchainImagesKHR(device.handle, swapchain->handle, &image_count, nullptr);

	swapchain->imgs.resize(image_count);
	vkGetSwapchainImagesKHR(device.handle, swapchain->handle, &image_count, swapchain->imgs.data());

	swapchain->views.resize(swapchain->imgs.size());

	for(uint32_t i = 0; i < swapchain->imgs.size(); ++i) {

		VkImageViewCreateInfo img_view_info = img_view_create_info(swapchain->imgs[i], swapchain->format);

		if (vkCreateImageView(device.handle, &img_view_info, nullptr, &swapchain->views[i]) != VK_SUCCESS) {
			log_critical("Failed to Create the ImageView!");
		}
	}

	log_success("The Image Views were Created!");
}

void img_view_destroy(const swapchain_t& swapchain, const device_t& device) 
{
	log_info("Destroying the Image Views...");

	for(auto& view : swapchain.views) {
		vkDestroyImageView(device.handle, view, nullptr);
	}

	log_success("The Image Views were Destroyed!");
}
