#include "engine/gfx/Renderer.hpp"
#include "engine/events/EventManager.hpp"
#include "engine/window/Window.hpp"
#include "core/vulkan/Core.hpp"
#include "util/debug/Logger.hpp"
#include "util/Constants.hpp"

#include <vulkan/vulkan.h>

#include <array>

void rndr_init(renderer_t *r, window_t *win) 
{
	log_info("Initializing a Renderer...");

	r->pwin = win;

	log_info("The Renderer was Initialized.");
}

void rndr_destroy(renderer_t *r) 
{
	log_info("Destroying the Renderer...");

	r->pwin = nullptr;

	log_info("The Renderer was Destroyed.");
}

void rndr_loop(renderer_t *r, event_manager_t *ev_m, core_t *core) 
{
	renderer_state_t st = {};
	while(!r->pwin->is_closed) {
		ev_m_poll(ev_m, &st, r->pwin);
		rndr_draw(*r, &st, core);
	}
	vkDeviceWaitIdle(core->dev.handle);
}

void rndr_draw(const renderer_t &r, renderer_state_t *st, core_t *core) 
{
	vkWaitForFences(core->dev.handle, 1, &core->frm_fences[st->frame].handle, VK_TRUE, UINT64_MAX);

	uint32_t img_idx;
	VkResult res = vkAcquireNextImageKHR(core->dev.handle, core->swp.handle, UINT64_MAX, core->img_avail_sems[st->frame].handle, VK_NULL_HANDLE, &img_idx);

	if (res == VK_ERROR_OUT_OF_DATE_KHR) {
		swp_recreate(&core->swp, &core->swp_st, core->dev, core->phys_dev, core->rp, core->qf, core->surf, *r.pwin);
		return;
	} else if (res != VK_SUCCESS && res != VK_SUBOPTIMAL_KHR) {
		log_critical("Failed to Acquire Swapchain Image.");
	}

	vkResetFences(core->dev.handle, 1, &core->frm_fences[st->frame].handle);

	vkResetCommandBuffer(core->cmd_bufs[st->frame].handle, 0);
	cmd_buf_record(core->cmd_bufs[st->frame], core->pipeline, vk_core->rp, core->swp_st, core->vert_buf, img_idx);

	std::array<VkSemaphore, 1> waits = {core->img_avail_sems[st->frame].handle};
	std::array<VkPipelineStageFlags, 1> stages = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	std::array<VkSemaphore, 1> signals = {core->rnd_done_sems[st->frame].handle};

	VkSubmitInfo submit_info = q_create_submit_info(st->frame, waits, signals, stages, core->cmd_bufs);

	if (vkQueueSubmit(core->q.graphics, 1, &submit_info, core->frm_fences[st->frame].handle) != VK_SUCCESS) {
		log_critical("Failed to Submit Draw Command Buffer.");
	}

	std::array<VkSwapchainKHR, 1> swps = {core->swp.handle};
	VkPresentInfoKHR p_info = q_create_pres_info(signals, swps, img_idx);

	vkQueuePresentKHR(core->q.present, &p_info);

	if (res == VK_ERROR_OUT_OF_DATE_KHR || res == VK_SUBOPTIMAL_KHR || st->fb_resized) {
		st->fb_resized = false;
		swp_recreate(&core->swp, &core->swp_st, core->dev, core->phys_dev, core->rp, core->qf, core->surf, *r.pwin);
	} else if (res != VK_SUCCESS) {
		log_critical("Failed to Present Swapchain Image.");
	}

	st->frame = (st->frame + 1) % MAX_FRAMES_IN_FLIGHT;
}
