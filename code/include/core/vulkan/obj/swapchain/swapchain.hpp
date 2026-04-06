#ifndef MOD_SWAPCHAIN_HPP
#define MOD_SWAPCHAIN_HPP

#include "core/vulkan/obj/image/image_view.hpp"
#include "core/vulkan/obj/image/image.hpp"

#include <vulkan/vulkan.h>

#include <vector>

struct window;
struct queue_indices;
struct physical_device;
struct render_pass;
struct device;
struct surface;

struct swapchain {
	VkSwapchainKHR handle = VK_NULL_HANDLE;
};

struct swapchain_support_details {
	VkSurfaceCapabilitiesKHR			caps;
	std::vector<VkSurfaceFormatKHR>			fmts;
	std::vector<VkPresentModeKHR>			pms;
};

struct swapchain_state {
	std::vector<VkFramebuffer>			fbs;
	std::vector<image_view>				views; 
	std::vector<image>				imgs;
};

swapchain_support_details swapchain_query_supp_details(const physical_device &gpu, const surface &surf);

VkSurfaceFormatKHR swapchain_choose_fmt(const std::vector<VkSurfaceFormatKHR> &fmts);

VkPresentModeKHR swapchain_choose_pm(const std::vector<VkPresentModeKHR> &pms);

VkExtent2D swapchain_choose_extent(const window &win, const VkSurfaceCapabilitiesKHR &caps);

VkSwapchainCreateInfoKHR swapchain_create_info(const queue_indices &q_idx, const surface &surf, const VkSurfaceFormatKHR &fmt, 
					       const VkPresentModeKHR &pm, const VkExtent2D &extent, 
					       const VkSurfaceCapabilitiesKHR &caps, const uint32_t img_cnt);

bool swapchain_is_adequate(const VkPhysicalDevice &gpu, const VkSurfaceKHR &surf);

void swapchain_state_setup(swapchain_state *st, const swapchain &swp, const device &dev, const VkSurfaceFormatKHR &fmt, 
			   const VkExtent2D &extent);

void swapchain_recreate(swapchain *swp, swapchain_state *st, const device &dev, const physical_device &gpu, const render_pass &rp, 
			const queue_indices &q_idx, const surface &surf, const window &win);

void swapchain_create(swapchain *swp, swapchain_state *st, const device &dev, const physical_device &gpu, 
		      const queue_indices &q_idx, const surface &surf, const window &win);

void swapchain_destroy(const swapchain &swp, const device &dev);

#endif
