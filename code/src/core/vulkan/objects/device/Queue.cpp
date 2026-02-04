#include "core/vulkan/objects/device/Queue.hpp"
#include "core/vulkan/objects/commands/CommandBuffer.hpp"

#include <vulkan/vulkan.h>

VkSubmitInfo queue_create_submit_info
(
	const uint32_t&					current_frame, 
	const std::array<VkSemaphore, 1>&		wait_semaphores,
	const std::array<VkSemaphore, 1>&		signal_semaphores,
	const std::array<VkPipelineStageFlags, 1>&	wait_stages, 
	const std::vector<command_buffer_t>&		command_buffers
)
{
	VkSubmitInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	create_info.waitSemaphoreCount = static_cast<uint32_t>(wait_semaphores.size());
	create_info.pWaitSemaphores = wait_semaphores.data();
	create_info.pWaitDstStageMask = wait_stages.data();
	create_info.commandBufferCount = 1;
	create_info.pCommandBuffers = &command_buffers[current_frame].handle;
	create_info.signalSemaphoreCount = static_cast<uint32_t>(signal_semaphores.size());
	create_info.pSignalSemaphores = signal_semaphores.data();
	return create_info;
}

VkPresentInfoKHR queue_create_present_info
(
	const std::array<VkSemaphore, 1>&	signal_semaphores,
	const std::array<VkSwapchainKHR, 1>&	swapchains, 
	const uint32_t&				img_idx
)
{
	VkPresentInfoKHR create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	create_info.waitSemaphoreCount = static_cast<uint32_t>(signal_semaphores.size());
	create_info.pWaitSemaphores = signal_semaphores.data();
	create_info.swapchainCount = static_cast<uint32_t>(swapchains.size());
	create_info.pSwapchains = swapchains.data();
	create_info.pImageIndices = &img_idx;
	create_info.pResults = nullptr;
	return create_info;
}
