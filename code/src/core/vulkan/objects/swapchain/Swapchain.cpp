#include "core/vulkan/objects/swapchain/Swapchain.hpp"
#include "core/vulkan/objects/swapchain/Framebuffer.hpp"
#include "core/vulkan/objects/swapchain/ImageView.hpp"
#include "core/vulkan/objects/device/QueueFamily.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "core/vulkan/objects/device/PhysicalDevice.hpp"
#include "core/vulkan/objects/instance/Surface.hpp"
#include "engine/window/Window.hpp"
#include "util/debug/Logger.hpp"

#include <array>
#include <limits>
#include <algorithm>

swapchain_support_detailts_t swp_query_supp_details(const VkPhysicalDevice &phys_dev, const VkSurfaceKHR &surf) 
{
	swapchain_support_detailts_t d;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(phys_dev, surf, &d.caps);

	uint32_t fmt_cnt;
	vkGetPhysicalDeviceSurfaceFormatsKHR(phys_dev, surf, &fmt_cnt, nullptr);

	if (fmt_cnt != 0) {
		d.fmts.resize(fmt_cnt);
		vkGetPhysicalDeviceSurfaceFormatsKHR(phys_dev, surf, &fmt_cnt, d.fmts.data());
	}

	uint32_t pm_cnt;
	vkGetPhysicalDeviceSurfacePresentModesKHR(phys_dev, surf, &pm_cnt, nullptr);

	if (pm_cnt != 0) {
		d.pms.resize(pm_cnt);
		vkGetPhysicalDeviceSurfacePresentModesKHR(phys_dev, surf, &pm_cnt, d.pms.data());
	}

	return d;
}

bool swp_is_adequate(const VkPhysicalDevice &phys_dev, const VkSurfaceKHR &surf) 
{
	swapchain_support_detailts_t d = swp_query_supp_details(phys_dev, surf);

	bool srgb_ok = false;
	for(const auto &fmt : d.fmts) {
		if ((fmt.format == VK_FORMAT_B8G8R8A8_SRGB || fmt.format == VK_FORMAT_UNDEFINED) && fmt.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			srgb_ok = true;
		}
	}

	bool pm_ok = false;
	for(const auto &pm: d.pms) {
		if (pm == VK_PRESENT_MODE_MAILBOX_KHR || pm == VK_PRESENT_MODE_FIFO_KHR) {
			pm_ok = true;
		}
	}

	return srgb_ok && pm_ok;
}

VkSurfaceFormatKHR swp_choose_fmt(const std::vector<VkSurfaceFormatKHR> &fmts) 
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

VkPresentModeKHR swp_choose_p_mode(const std::vector<VkPresentModeKHR> &pms) 
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

VkExtent2D swp_choose_extent(const window_t &win, const VkSurfaceCapabilitiesKHR &caps) 
{
	log_info("Choosing the Swapchain Extent..."); 

	if(caps.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		log_info("The Swapchain Extent was Chosen.");
		return caps.currentExtent;
	} else {
		int w, h;
		SDL_GetWindowSizeInPixels(win.handle, &w, &h); 

		VkExtent2D extent 
		{
			static_cast<uint32_t>(w),
			static_cast<uint32_t>(h)
		};

		extent.width = std::clamp(extent.width, caps.minImageExtent.width, caps.maxImageExtent.width);
		extent.height = std::clamp(extent.height, caps.minImageExtent.height, caps.maxImageExtent.height);

		log_info("The Swapchain Extent was Chosen.");

		return extent;
	}
}

VkSwapchainCreateInfoKHR swp_create_info
(
	const queue_family_t				&qf,
	const surface_t					&surf,
	const VkSurfaceFormatKHR			&fmt, 
	const VkPresentModeKHR				&pm, 
	const VkExtent2D				&extent, 
	const VkSurfaceCapabilitiesKHR			&caps, 
	const uint32_t					 img_cnt
)
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

	const std::array<uint32_t, 2> qf_idxs = {qf.gfx.value(), qf.pres.value()};

	if(qf.gfx!= qf.pres) {
		info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		info.queueFamilyIndexCount = 2;
		info.pQueueFamilyIndices = qf_idxs.data();
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

void swp_st_setup(swapchain_state_t *st, const swapchain_t &swp, const device_t &dev, const VkSurfaceFormatKHR &fmt, const VkExtent2D &extent)
{
	st->fmt = fmt.format;
	st->extent = extent;

	uint32_t img_cnt = 0;
	vkGetSwapchainImagesKHR(dev.handle, swp.handle, &img_cnt, nullptr);

	st->imgs.resize(img_cnt);
	vkGetSwapchainImagesKHR(dev.handle, swp.handle, &img_cnt, st->imgs.data());
}

void swp_recreate
(
	swapchain_t				*swp, 
	swapchain_state_t			*st, 
	const device_t				&dev, 
	const phys_device_t			&phys_dev, 
	const render_pass_t			&rp, 
	const queue_family_t			&qf, 
	const surface_t				&surf,
	const window_t				&win
)
{
	vkDeviceWaitIdle(dev.handle);

	fbs_destroy(*st, dev);
	img_views_destroy(*st, dev);
	swp_destroy(*swp, dev);
	
	swp_create(swp, st, dev, phys_dev, qf, surf, win);
	img_views_create(st, dev);
	fbs_create(st, dev, rp);
}

void swp_create(swapchain_t *swp, swapchain_state_t *st, const device_t &dev, const phys_device_t &phys_dev, const queue_family_t &qf, const surface_t &surf, const window_t &win)
{
	log_info("Creating a Swapchain...");

	swapchain_support_detailts_t d = swp_query_supp_details(phys_dev.handle, surf.handle);
	VkSurfaceFormatKHR fmt = swp_choose_fmt(d.fmts);
	VkPresentModeKHR pm = swp_choose_p_mode(d.pms);
	VkExtent2D extent = swp_choose_extent(win, d.caps);

	uint32_t img_cnt = d.caps.minImageCount + 1;

	if (d.caps.maxImageCount > 0 && img_cnt > d.caps.maxImageCount) {
		img_cnt = d.caps.maxImageCount;
	}

	VkSwapchainCreateInfoKHR info = swp_create_info(qf, surf, fmt, pm, extent, d.caps, img_cnt);

	if (vkCreateSwapchainKHR(dev.handle, &info, nullptr, &swp->handle) != VK_SUCCESS) {
		log_critical("Failed to Create the Swapchain.");
	}

	swp_st_setup(st, *swp, dev, fmt, extent);

	log_info("The Swapchain was Created.");
}

void swp_destroy(const swapchain_t &swp, const device_t &dev) 
{
	log_info("Destroying the Swapchain...");

	if (swp.handle == VK_NULL_HANDLE) {
		log_error("Cannot Destroy the Swapchain::Swapchain is not Created.");
	}

	vkDestroySwapchainKHR(dev.handle, swp.handle, nullptr);

	log_info("The Swapchain was Destroyed.");
}
