#include "engine/gfx/renderer.hpp"
#include "engine/event/event_manager.hpp"
#include "engine/window/window.hpp"
#include "core/vulkan/core.hpp"
#include "util/debug/log.hpp"
#include "util/constants.hpp"

#include <vulkan/vulkan.h>

#include <array>

void renderer_init(renderer *r, window *win) 
{
	log_info("Initializing a Renderer...");

	r->pwin = win;

	log_info("The Renderer was Initialized.");
}

void renderer_destroy(renderer *r) 
{
	log_info("Destroying the Renderer...");

	r->pwin = nullptr;

	log_info("The Renderer was Destroyed.");
}

void renderer_loop(renderer *r, event_manager *ev_m, core *c) 
{
	renderer_state st = {};
	while(!r->pwin->is_closed) {
		event_manager_poll(ev_m, &st, r->pwin);
		renderer_draw(*r, &st, c);
	}
	vkDeviceWaitIdle(c->dev.handle);
}

void renderer_draw(const renderer &r, renderer_state *st, core *c) 
{
	vkWaitForFences(c->dev.handle, 1, &c->frm_fences[st->frame].handle, VK_TRUE, UINT64_MAX);

	uint32_t img_idx;
	VkResult res = vkAcquireNextImageKHR(c->dev.handle, c->swp.handle, UINT64_MAX, c->img_avail_sems[st->frame].handle, VK_NULL_HANDLE, &img_idx);

	if (res == VK_ERROR_OUT_OF_DATE_KHR) {
		swapchain_recreate(&c->swp, &c->swp_st, c->dev, c->gpu, c->rp, c->q_idx, c->surf, *r.pwin);
		return;
	} else if (res != VK_SUCCESS && res != VK_SUBOPTIMAL_KHR) {
		log_critical("Failed to Acquire Swapchain Image.");
	}

	vkResetFences(c->dev.handle, 1, &c->frm_fences[st->frame].handle);

	vkResetCommandBuffer(c->cmds[st->frame].handle, 0);
	command_buffer_record(c->cmds[st->frame], c->pl, c->rp, c->swp_st, c->buf, img_idx);

	std::array<VkSemaphore, 1> waits = {c->img_avail_sems[st->frame].handle};
	std::array<VkPipelineStageFlags, 1> stages = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	std::array<VkSemaphore, 1> signals = {c->rnd_done_sems[st->frame].handle};

	VkSubmitInfo submit_info = queue_create_submit_info(st->frame, waits, signals, stages, c->cmds);

	if (vkQueueSubmit(c->q.gfx, 1, &submit_info, c->frm_fences[st->frame].handle) != VK_SUCCESS)
		log_critical("Failed to Submit Draw Command Buffer.");

	std::array<VkSwapchainKHR, 1> swps = {c->swp.handle};
	VkPresentInfoKHR pres_info = queue_create_pres_info(signals, swps, img_idx);

	vkQueuePresentKHR(c->q.pres, &pres_info);

	if (res == VK_ERROR_OUT_OF_DATE_KHR || res == VK_SUBOPTIMAL_KHR || st->fb_resized) {
		st->fb_resized = false;
		swapchain_recreate(&c->swp, &c->swp_st, c->dev, c->gpu, c->rp, c->q_idx, c->surf, *r.pwin);
	} else if (res != VK_SUCCESS) {
		log_critical("Failed to Present Swapchain Image.");
	}

	st->frame = (st->frame + 1) % MAX_FRAMES_IN_FLIGHT;
}
