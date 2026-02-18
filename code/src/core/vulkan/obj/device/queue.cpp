#include "core/vulkan/obj/device/queue.hpp"
#include "core/vulkan/obj/command/command_buffer.hpp"

#include <vulkan/vulkan.h>

VkSubmitInfo queue_create_submit_info(const uint32_t &frame, const std::array<VkSemaphore, 1> &waits, const std::array<VkSemaphore, 1> &signals, 
				  const std::array<VkPipelineStageFlags, 1> &stages, const std::vector<command_buffer> &cmds)
{
	VkSubmitInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	info.waitSemaphoreCount = static_cast<uint32_t>(waits.size());
	info.pWaitSemaphores = waits.data();
	info.pWaitDstStageMask = stages.data();
	info.commandBufferCount = 1;
	info.pCommandBuffers = &cmds[frame].handle;
	info.signalSemaphoreCount = static_cast<uint32_t>(signals.size());
	info.pSignalSemaphores = signals.data();
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
