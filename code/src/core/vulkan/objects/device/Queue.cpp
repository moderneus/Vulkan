#include "core/vulkan/objects/device/Queue.hpp"
#include "core/vulkan/objects/commands/CommandBuffer.hpp"

#include <vulkan/vulkan.h>

VkSubmitInfo q_create_submit_info
(
	const uint32_t						&frame,
	const std::array<VkSemaphore, 1>			&waits,
	const std::array<VkSemaphore, 1>			&signals,
	const std::array<VkPipelineStageFlags, 1>		&stages, 
	const std::vector<command_buffer_t>			&cmd_bufs
)
{
	VkSubmitInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	info.waitSemaphoreCount = static_cast<uint32_t>(waits.size());
	info.pWaitSemaphores = waits.data();
	info.pWaitDstStageMask = stages.data();
	info.commandBufferCount = 1;
	info.pCommandBuffers = &cmd_bufs[frame].handle;
	info.signalSemaphoreCount = static_cast<uint32_t>(signals.size());
	info.pSignalSemaphores = signals.data();
	return info;
}

VkPresentInfoKHR q_create_pres_info
(
	const std::array<VkSemaphore, 1>			&signals,
	const std::array<VkSwapchainKHR, 1>			&swapchains, 
	const uint32_t						&img_idx
)
{
	VkPresentInfoKHR info = {};
	info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	info.waitSemaphoreCount = static_cast<uint32_t>(signals.size());
	info.pWaitSemaphores = signals.data();
	info.swapchainCount = static_cast<uint32_t>(swapchains.size());
	info.pSwapchains = swapchains.data();
	info.pImageIndices = &img_idx;
	info.pResults = nullptr;
	return info;
}
