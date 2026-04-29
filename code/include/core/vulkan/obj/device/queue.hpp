#ifndef MOD_QUEUE_HPP
#define MOD_QUEUE_HPP

#include <vulkan/vulkan.h>

#include <vector>
#include <array>

struct swapchain;
struct command_buffer;
struct semaphore;

struct queue {
	VkQueue	gfx  = VK_NULL_HANDLE;
	VkQueue	pres = VK_NULL_HANDLE;
	VkQueue comp = VK_NULL_HANDLE;
};

VkSubmitInfo queue_create_submit_info(const uint32_t &frame, const std::array<VkSemaphore, 2> &waits, const std::array<VkSemaphore, 1> &signals, 
				      const std::array<VkPipelineStageFlags, 2> &stages, const std::vector<command_buffer> &cmds);

VkSubmitInfo queue_create_compute_submit_info(const uint32_t &frame, const std::vector<command_buffer> &cmds, const std::array<VkSemaphore, 1> &comp_done_sems);

VkPresentInfoKHR queue_create_pres_info(const std::array<VkSemaphore, 1> &signals, const std::array<VkSwapchainKHR, 1> &swps, const uint32_t &img_idx);

#endif
