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
	VkQueue		gfx = VK_NULL_HANDLE;
	VkQueue		pres = VK_NULL_HANDLE;
};

VkSubmitInfo q_create_submit_info
(
	const uint32_t						&frame, 
	const std::array<VkSemaphore, 1>			&waits,
	const std::array<VkSemaphore, 1>			&signals,
	const std::array<VkPipelineStageFlags, 1>		&stages, 
	const std::vector<command_buffer_t>			&cmd_bufs
);

VkPresentInfoKHR q_create_pres_info
(
	const std::array<VkSemaphore, 1>			&signals,
	const std::array<VkSwapchainKHR, 1>			&swapchains, 
	const uint32_t						&img_idx
);

#endif
