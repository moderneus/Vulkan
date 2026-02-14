#ifndef MOD_SWAPCHAIN_HPP
#define MOD_SWAPCHAIN_HPP

#include <vulkan/vulkan.h>

#include <vector>

struct window_t;
struct queue_family_t;
struct phys_device_t;
struct render_pass_t;
struct device_t;
struct surface_t;

struct swapchain_t
{
	VkSwapchainKHR handle = VK_NULL_HANDLE;
};

struct swapchain_support_detailts_t
{
	VkSurfaceCapabilitiesKHR			caps;
	std::vector<VkSurfaceFormatKHR>			fmts;
	std::vector<VkPresentModeKHR>			pms;
};

struct swapchain_state_t
{
	VkExtent2D					extent = {};
	VkFormat					fmt = VK_FORMAT_UNDEFINED;
	VkColorSpaceKHR					colspc = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	std::vector<VkFramebuffer>			fbs;
	std::vector<VkImageView>			views; 
	std::vector<VkImage>				imgs;
};

swapchain_support_detailts_t swp_query_supp_details(const phys_device_t &phys_dev, const surface_t &surf);

VkSurfaceFormatKHR swp_choose_fmt(const std::vector<VkSurfaceFormatKHR> &fmts);

VkPresentModeKHR swp_choose_pm(const std::vector<VkPresentModeKHR> &pms);

VkExtent2D swp_choose_extent(const window_t &window, const VkSurfaceCapabilitiesKHR &caps);

VkSwapchainCreateInfoKHR swp_create_info
(
	const queue_family_t				&qf,
	const surface_t					&surf,
	const VkSurfaceFormatKHR			&fmt, 
	const VkPresentModeKHR				&pm, 
	const VkExtent2D				&extent, 
	const VkSurfaceCapabilitiesKHR			&caps, 
	const uint32_t					 img_cnt
);

bool swp_is_adequate(const VkPhysicalDevice &phys_dev, const VkSurfaceKHR &surf);

void swp_st_setup(swapchain_state_t *st, const swapchain_t &swp, const device_t &dev, const VkSurfaceFormatKHR &fmt, const VkExtent2D& extent);

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
);

void swp_create(swapchain_t *swp, swapchain_state_t *st, const device_t &dev, const phys_device_t &phys_dev, const queue_family_t &qf, const surface_t &surf, const window_t &win);

void swp_destroy(const swapchain_t &swp, const device_t &dev);

#endif
