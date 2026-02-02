#include "engine/gfx/Renderer.hpp"
#include "engine/events/EventManager.hpp"
#include "engine/window/Window.hpp"
#include "core/vulkan/Core.hpp"
#include "util/debug/Logger.hpp"
#include "util/Constants.hpp"

#include <vulkan/vulkan.h>

#include <array>

void renderer_init(renderer_t* renderer, window_t* pwindow) 
{
	log_info("Initializing a Renderer...");

	renderer->pwindow = pwindow;

	log_info("The Renderer was Initialized.");
}

void renderer_destroy(renderer_t* renderer) 
{
	log_info("Destroying the Renderer...");

	renderer->pwindow = nullptr;

	log_info("The Renderer was Destroyed.");
}

void renderer_loop(renderer_t* renderer, event_manager_t* event_manager, core_t* vk_core) 
{
	renderer_config_t cfg = {};
	while(!renderer->pwindow->is_closed) {
		event_manager_poll_events(event_manager, &cfg, renderer->pwindow);
		renderer_draw(*renderer, &cfg, vk_core);
	}
	vkDeviceWaitIdle(vk_core->device.handle);
}

void renderer_draw(const renderer_t& renderer, renderer_config_t* cfg, core_t* vk_core) 
{
	vkWaitForFences(vk_core->device.handle, 1, &vk_core->in_flight_fences[cfg->current_frame].handle, VK_TRUE, UINT64_MAX);

	uint32_t img_idx;
	VkResult res = vkAcquireNextImageKHR(vk_core->device.handle, vk_core->swapchain.handle, UINT64_MAX, vk_core->img_available_semaphores[cfg->current_frame].handle, VK_NULL_HANDLE, &img_idx);

	if (res == VK_ERROR_OUT_OF_DATE_KHR) {
		swapchain_recreate(&vk_core->swapchain, &vk_core->swapchain_cfg, vk_core->device, vk_core->phys_device, vk_core->render_pass, vk_core->queue_family, vk_core->surface, *renderer.pwindow);
		return;
	} else if (res != VK_SUCCESS && res != VK_SUBOPTIMAL_KHR) {
		log_critical("Failed to Acquire Swapchain Image.");
	}

	vkResetFences(vk_core->device.handle, 1, &vk_core->in_flight_fences[cfg->current_frame].handle);

	vkResetCommandBuffer(vk_core->command_buffers[cfg->current_frame].handle, 0);
	command_buffer_record(vk_core->command_buffers[cfg->current_frame], vk_core->pipeline, vk_core->render_pass, vk_core->swapchain_cfg, img_idx);

	std::array<VkSemaphore, 1> wait_semaphores = {vk_core->img_available_semaphores[cfg->current_frame].handle};
	std::array<VkPipelineStageFlags, 1> wait_stages = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	std::array<VkSemaphore, 1> signal_semaphores = {vk_core->render_finished_semaphores[cfg->current_frame].handle};

	VkSubmitInfo submit_info = queue_create_submit_info(cfg->current_frame, wait_semaphores, signal_semaphores, wait_stages, vk_core->command_buffers);

	if (vkQueueSubmit(vk_core->queue.graphics, 1, &submit_info, vk_core->in_flight_fences[cfg->current_frame].handle) != VK_SUCCESS) {
		log_critical("Failed to Submit Draw Command Buffer.");
	}

	std::array<VkSwapchainKHR, 1> swapchains = {vk_core->swapchain.handle};
	VkPresentInfoKHR present_info = queue_create_present_info(signal_semaphores, swapchains, img_idx);

	vkQueuePresentKHR(vk_core->queue.present, &present_info);

	if (res == VK_ERROR_OUT_OF_DATE_KHR || res == VK_SUBOPTIMAL_KHR || cfg->framebuffer_resized) {
		cfg->framebuffer_resized = false;
		swapchain_recreate(&vk_core->swapchain, &vk_core->swapchain_cfg, vk_core->device, vk_core->phys_device, vk_core->render_pass, vk_core->queue_family, vk_core->surface, *renderer.pwindow);
	} else if (res != VK_SUCCESS) {
		log_critical("Failed to Present Swapchain Image.");
	}

	cfg->current_frame = (cfg->current_frame + 1) % MAX_FRAMES_IN_FLIGHT;
}
