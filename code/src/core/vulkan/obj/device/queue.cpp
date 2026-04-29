#include "core/vulkan/obj/device/queue.hpp"
#include "core/vulkan/obj/command/command_buffer.hpp"

#include <vulkan/vulkan.h>

VkSubmitInfo queue_create_submit_info(const uint32_t &frame, const std::array<VkSemaphore, 2> &waits, const std::array<VkSemaphore, 1> &signals, 
				  const std::array<VkPipelineStageFlags, 2> &stages, const std::vector<command_buffer> &cmds)
{
	VkSubmitInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	info.waitSemaphoreCount = 2;
	info.pWaitSemaphores = waits.data();
	info.pWaitDstStageMask = stages.data();
	info.commandBufferCount = 1;
	info.pCommandBuffers = &cmds[frame].handle;
	info.signalSemaphoreCount = 1;
	info.pSignalSemaphores = signals.data();
	return info;
}

VkSubmitInfo queue_create_compute_submit_info(const uint32_t &frame, const std::vector<command_buffer> &cmds, const std::array<VkSemaphore, 1> &comp_done_sems)
{
	VkSubmitInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	info.commandBufferCount = 1;
	info.pCommandBuffers = &cmds[frame].handle;
	info.signalSemaphoreCount = 1;
	info.pSignalSemaphores = comp_done_sems.data();
	return info;
}

VkPresentInfoKHR queue_create_pres_info(const std::array<VkSemaphore, 1> &signals, const std::array<VkSwapchainKHR, 1> &swps, const uint32_t &img_idx)
{
	VkPresentInfoKHR info = {};
	info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	info.waitSemaphoreCount = static_cast<uint32_t>(signals.size());
	info.pWaitSemaphores = signals.data();
	info.swapchainCount = static_cast<uint32_t>(swps.size());
	info.pSwapchains = swps.data();
	info.pImageIndices = &img_idx;
	info.pResults = nullptr;
	return info;
}
