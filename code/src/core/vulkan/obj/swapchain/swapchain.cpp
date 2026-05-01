#include "core/vulkan/obj/swapchain/swapchain.hpp"
#include "core/vulkan/obj/swapchain/framebuffer.hpp"
#include "core/vulkan/obj/device/queue_indices.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "core/vulkan/obj/device/physical_device.hpp"
#include "core/vulkan/obj/image/depth_image.hpp"
#include "core/vulkan/obj/instance/surface.hpp"
#include "engine/window/window.hpp"
#include "util/debug/log.hpp"

#include "SDL3/SDL_events.h"

#include <array>
#include <limits>
#include <algorithm>

swapchain_support_details swapchain_query_supp_details(const VkPhysicalDevice &gpu, const VkSurfaceKHR &surf) 
{
	log_info("Querying the Swapchain Support Details...");

	swapchain_support_details d;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(gpu, surf, &d.caps);

	uint32_t fmt_cnt;
	vkGetPhysicalDeviceSurfaceFormatsKHR(gpu, surf, &fmt_cnt, nullptr);

	if (fmt_cnt != 0) {
		d.fmts.resize(fmt_cnt);
		vkGetPhysicalDeviceSurfaceFormatsKHR(gpu, surf, &fmt_cnt, d.fmts.data());
	}

	uint32_t pm_cnt;
	vkGetPhysicalDeviceSurfacePresentModesKHR(gpu, surf, &pm_cnt, nullptr);

	if (pm_cnt != 0) {
		d.pms.resize(pm_cnt);
		vkGetPhysicalDeviceSurfacePresentModesKHR(gpu, surf, &pm_cnt, d.pms.data());
	}

	log_info("The Swapchain Support Details were Returned.");

	return d;
}

bool swapchain_is_adequate(const VkPhysicalDevice &gpu, const VkSurfaceKHR &surf) 
{
	log_info("Checking an Adequacy of Swapchain...");

	swapchain_support_details d = swapchain_query_supp_details(gpu, surf);

	bool srgb_ok = false;
	for(const auto &fmt : d.fmts) {
		if ((fmt.format == VK_FORMAT_B8G8R8A8_SRGB || fmt.format == VK_FORMAT_UNDEFINED) && 
		     fmt.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			srgb_ok = true;
	}

	bool pm_ok = false;
	for(const auto &pm: d.pms) {
		if (pm == VK_PRESENT_MODE_MAILBOX_KHR || pm == VK_PRESENT_MODE_FIFO_KHR)
			pm_ok = true;
	}

	if (!(srgb_ok && pm_ok))
		log_critical("The Swapchain is not Adequate.");

	log_info("The Swapchain is Adequate.");

	return srgb_ok && pm_ok;
}

VkSurfaceFormatKHR swapchain_choose_fmt(const std::vector<VkSurfaceFormatKHR> &fmts) 
{
	log_info("Choosing the Swapchain Format...");

	if(fmts.size() == 1 && fmts[0].format == VK_FORMAT_UNDEFINED) {
		log_info("The Swapchain Format Was Chosen.");
		return {VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
	}

	for(const auto &fmt : fmts) {
		if (fmt.format == VK_FORMAT_B8G8R8A8_SRGB && fmt.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			log_info("The Swapchain Format was Chosen.");
			return fmt;
		}
	}

	log_info("The Swapchain Format was Chosen.");

	return fmts[0];
}

VkPresentModeKHR swapchain_choose_pm(const std::vector<VkPresentModeKHR> &pms) 
{
	log_info("Choosing the Swapchain Present Mode...");

	for(const auto &pm : pms) {
		if (pm == VK_PRESENT_MODE_MAILBOX_KHR) {
			log_info("The Swapchain Present Mode was Chosen = VK_PRESENT_MODE_MAILBOX_KHR.");
			return pm;
		}
	}

	log_info("The Swapchain Present Mode was Chosen = VK_PRESENT_MODE_FIFO_KHR.");

	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D swapchain_choose_extent(const window &win, const VkSurfaceCapabilitiesKHR &caps) 
{
	log_info("Choosing the Swapchain Extent..."); 

	if(caps.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		log_info("The Swapchain Extent was Chosen.");
		return caps.currentExtent;
	} else {
		int w, h;
		SDL_GetWindowSizeInPixels(win.handle, &w, &h); 

		VkExtent2D extent { static_cast<uint32_t>(w), static_cast<uint32_t>(h) };

		extent.width = std::clamp(extent.width, caps.minImageExtent.width, caps.maxImageExtent.width);
		extent.height = std::clamp(extent.height, caps.minImageExtent.height, caps.maxImageExtent.height);

		log_info("The Swapchain Extent was Chosen.");

		return extent;
	}
}

VkSwapchainCreateInfoKHR swapchain_create_info(const queue_indices &q_idx, const surface &surf, const VkSurfaceFormatKHR &fmt, const VkPresentModeKHR &pm, const VkExtent2D &extent, 
					       const VkSurfaceCapabilitiesKHR &caps, const uint32_t img_cnt)
{
	log_info("Creating the Swapchain Info...");

	VkSwapchainCreateInfoKHR info = {};
	info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	info.surface = surf.handle;
	info.minImageCount = img_cnt;
	info.imageColorSpace = fmt.colorSpace;
	info.imageFormat = fmt.format;
	info.imageExtent = extent;
	info.imageArrayLayers = 1;
	info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	const std::array<uint32_t, 2> q_idxs = {q_idx.gfx.value(), q_idx.pres.value()};

	if(q_idx.gfx != q_idx.pres) {
		info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		info.queueFamilyIndexCount = 2;
		info.pQueueFamilyIndices = q_idxs.data();
	} else {
		info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		info.queueFamilyIndexCount = 0;
		info.pQueueFamilyIndices = nullptr;
	}

	info.preTransform = caps.currentTransform;
	info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	info.presentMode = pm;
	info.clipped = VK_TRUE;
	info.oldSwapchain = VK_NULL_HANDLE;

	log_info("The Swapchain Info was Created.");

	return info;
}

void swapchain_state_setup(swapchain_state *st, const swapchain &swp, const device &dev, 
			   const VkSurfaceFormatKHR &fmt, const VkExtent2D &extent)
{
	log_info("Setting up the Swapchain State...");

	uint32_t img_cnt = 0;
	vkGetSwapchainImagesKHR(dev.handle, swp.handle, &img_cnt, nullptr);

	std::vector<VkImage> tmp_imgs(img_cnt);
	vkGetSwapchainImagesKHR(dev.handle, swp.handle, &img_cnt, tmp_imgs.data());

	st->imgs.resize(img_cnt);

	for(uint32_t i = 0; i < img_cnt; ++i) {
		st->imgs[i].handle = tmp_imgs[i];
		st->imgs[i].fmt = fmt.format;
		st->imgs[i].extent = extent;
		st->imgs[i].aspect_flags = VK_IMAGE_ASPECT_COLOR_BIT;
		st->imgs[i].mip_lvls = 1;
	}

	log_info("The Swapchain State was Setted up.");
}

void swapchain_recreate(swapchain *swp, swapchain_state *swp_st, renderer_state *rnd_st, const device &dev, const physical_device &gpu, 
			const render_pass &rp, const queue_indices &q_idx, const surface &surf, const window &win)
{
	int w = 0, h = 0;
	SDL_Event e;
	while(w == 0 || h == 0) {
		SDL_GetWindowSizeInPixels(win.handle, &w, &h);
		SDL_WaitEvent(&e);

		if (e.type == SDL_EVENT_WINDOW_RESIZED)
			rnd_st->fb_resized = true;
	}

	vkDeviceWaitIdle(dev.handle);

	framebuffers_destroy(*swp_st, dev);
	color_image_destroy(*swp_st, dev);
	depth_image_destroy(*swp_st, dev);
	image_views_destroy(*swp_st, dev);
	swapchain_destroy(*swp, dev);
	
	swapchain_create(swp, swp_st, dev, gpu, q_idx, surf, win);
	image_views_create(swp_st, dev);
	depth_image_create(swp_st, dev, gpu);
	color_image_create(swp_st, dev, gpu);
	framebuffers_create(swp_st, dev, rp);
}

void swapchain_create(swapchain *swp, swapchain_state *st, const device &dev, const physical_device &gpu,
		      const queue_indices &q_idx, const surface &surf, const window &win)
{
	log_info("Creating a Swapchain...");

	swapchain_support_details d = swapchain_query_supp_details(gpu.handle, surf.handle);
	VkSurfaceFormatKHR fmt = swapchain_choose_fmt(d.fmts);
	VkPresentModeKHR pm = swapchain_choose_pm(d.pms);
	VkExtent2D extent = swapchain_choose_extent(win, d.caps);

	uint32_t img_cnt = d.caps.minImageCount + 1;

	if (d.caps.maxImageCount > 0 && img_cnt > d.caps.maxImageCount)
		img_cnt = d.caps.maxImageCount;

	VkSwapchainCreateInfoKHR info = swapchain_create_info(q_idx, surf, fmt, pm, extent, d.caps, img_cnt);

	if (vkCreateSwapchainKHR(dev.handle, &info, nullptr, &swp->handle) != VK_SUCCESS)
		log_critical("Failed to Create the Swapchain.");

	swapchain_state_setup(st, *swp, dev, fmt, extent);

	log_info("The Swapchain was Created.");
}

void swapchain_destroy(const swapchain &swp, const device &dev)
{
	log_info("Destroying the Swapchain...");

	if (swp.handle == VK_NULL_HANDLE)
		log_error("Cannot Destroy the Swapchain::Swapchain is not Created.");

	vkDestroySwapchainKHR(dev.handle, swp.handle, nullptr);

	log_info("The Swapchain was Destroyed.");
}
