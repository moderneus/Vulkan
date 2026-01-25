#ifndef MOD_SWAPCHAIN_HPP
#define MOD_SWAPCHAIN_HPP

#include <vulkan/vulkan.h>

#include <vector>

struct window_t;
struct queue_family_t;
struct phys_device_t;
struct device_t;
struct surface_t;

struct swapchain_support_detailts_t
{
	VkSurfaceCapabilitiesKHR		capabilities;
	std::vector<VkSurfaceFormatKHR>		formats;
	std::vector<VkPresentModeKHR>		present_modes;
};

struct swapchain_t
{
	VkSwapchainKHR handle = VK_NULL_HANDLE;
};

struct swapchain_config_t
{
	VkExtent2D			extent = {};
	VkFormat			format = VK_FORMAT_UNDEFINED;
	VkColorSpaceKHR			color_space = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
	std::vector<VkFramebuffer>	frame_buffers;
	std::vector<VkImageView>	views; 
	std::vector<VkImage>		imgs;
};

swapchain_support_detailts_t swapchain_query_support_details(const phys_device_t& phys_device, const surface_t& surface);

VkSurfaceFormatKHR swapchain_choose_format(const std::vector<VkSurfaceFormatKHR>& formats);

VkPresentModeKHR swapchain_choose_present_mode(const std::vector<VkPresentModeKHR>& present_modes);

VkExtent2D swapchain_choose_extent(const window_t& window, const VkSurfaceCapabilitiesKHR& capabilities);

VkSwapchainCreateInfoKHR swapchain_create_info
(
	const queue_family_t&			queue_family,
	const surface_t&			surface,
	const VkSurfaceFormatKHR&		format, 
	const VkPresentModeKHR&			present_mode, 
	const VkExtent2D&			extent, 
	const VkSurfaceCapabilitiesKHR&		capabilities, 
	const uint32_t				img_count
);

bool swapchain_is_adequate(const VkPhysicalDevice& phys_device, const VkSurfaceKHR& surface);

void swapchain_config_setup(swapchain_config_t* cfg, const swapchain_t& swapchain, const device_t& device, const VkSurfaceFormatKHR& format, const VkExtent2D& extent);

void swapchain_create(swapchain_t* swapchain, swapchain_config_t* cfg, const device_t& device, const phys_device_t& phys_device, const queue_family_t& queue_family, const window_t& window, const surface_t& surface);

void swapchain_destroy(const swapchain_t& swapchain, const device_t& device);

#endif
