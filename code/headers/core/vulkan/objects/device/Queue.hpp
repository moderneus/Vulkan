#ifndef MOD_QUEUE_HPP
#define MOD_QUEUE_HPP

#include <vulkan/vulkan.h>

#include <vector>
#include <array>

struct swapchain_t;
struct command_buffer_t;
struct semaphore_t;

struct queue_t
{
	VkQueue		graphics = VK_NULL_HANDLE;
	VkQueue		present  = VK_NULL_HANDLE;
};

VkSubmitInfo queue_create_submit_info
(
	const uint32_t&					current_frame, 
	const std::array<VkSemaphore, 1>&		wait_semaphores,
	const std::array<VkSemaphore, 1>&		signal_semaphores,
	const std::array<VkPipelineStageFlags, 1>&	wait_stages, 
	const std::vector<command_buffer_t>&		command_buffers
);

VkPresentInfoKHR queue_create_present_info
(
	const std::array<VkSemaphore, 1>&		signal_semaphores,
	const std::array<VkSwapchainKHR, 1>&		swapchains, 
	const uint32_t&					img_idx
);

#endif
