#include "core/vulkan/core.hpp"
#include "core/vulkan/obj/swapchain/framebuffer.hpp"
#include "util/debug/log.hpp"

void core_init(core *c, const window &win) 
{
	log_info("Initializing a Core...");

	instance_create(&c->inst);
	messenger_setup(&c->msgr, c->inst);
	surface_create(&c->surf, c->inst, win);
	physical_device_pick(&c->gpu, c->inst, c->surf);
	queue_indices_find(&c->q_idx, c->gpu, c->surf);
	device_create(&c->dev, &c->q, c->q_idx, c->gpu);
	swapchain_create(&c->swp, &c->swp_st, c->dev, c->gpu, c->q_idx, c->surf, win);
	image_views_create(&c->swp_st, c->dev);
	render_pass_create(&c->rp, c->dev, c->swp_st);
	shaders_create(&c->shdrs, c->dev);
	descriptor_set_layout_create(&c->set_lyt, c->dev);
	pipeline_layout_create(&c->lyt, c->dev, c->set_lyt);
	pipeline_create(&c->pl, c->dev, c->lyt, c->rp, c->swp_st, c->shdrs);
	framebuffers_create(&c->swp_st, c->dev, c->rp);
	command_pool_create(&c->cmd_pool, c->dev, c->q_idx);
	command_buffers_create(&c->cmds, c->dev, c->cmd_pool);
	vertex_buffer_create(&c->vert_buf, c->dev, c->gpu, c->q, c->cmd_pool);
	index_buffer_create(&c->idx_buf, c->dev, c->gpu, c->q, c->cmd_pool);
	texture_create(&c->tex, c->dev, c->gpu, c->q, c->cmd_pool, "assets/textures/texture.png");
	image_view_create(&c->tex_view, c->dev, c->tex.img);
	sampler_create(&c->samp, c->dev, c->gpu);
	uniform_buffer_create(&c->uniform_bufs, c->dev, c->gpu);
	descriptor_pool_create(&c->set_pool, c->dev);
	descriptor_sets_create(&c->sets, c->dev, c->set_pool, c->set_lyt, c->uniform_bufs, c->tex_view, c->samp);
	semaphores_create(&c->img_avail_sems, c->dev);
	semaphores_create(&c->rnd_done_sems, c->dev);
	fences_create(&c->frm_fences, c->dev);

	log_info("The Core was Initialized."); 
}

void core_destroy(core *c) 
{
	log_info("Destroying the Core...");

	fences_destroy(c->frm_fences, c->dev);
	semaphores_destroy(c->rnd_done_sems, c->dev);
	semaphores_destroy(c->img_avail_sems, c->dev);
	descriptor_pool_destroy(c->set_pool, c->dev);
	uniform_buffer_destroy(c->uniform_bufs, c->dev);
	sampler_destroy(c->samp, c->dev);
	image_view_destroy(c->tex_view, c->dev);
	texture_destroy(c->tex, c->dev);
	index_buffer_destroy(c->idx_buf, c->dev);
	vertex_buffer_destroy(c->vert_buf, c->dev);
	command_pool_destroy(c->cmd_pool, c->dev);
	framebuffers_destroy(c->swp_st, c->dev);
	pipeline_destroy(c->pl, c->dev);
	descriptor_set_layout_destroy(c->set_lyt, c->dev);
	shaders_destroy(c->shdrs, c->dev);
	render_pass_destroy(c->rp, c->dev);
	pipeline_layout_destroy(c->lyt, c->dev);
	image_views_destroy(c->swp_st, c->dev);
	swapchain_destroy(c->swp, c->dev);
	device_destroy(c->dev);
	surface_destroy(c->surf, c->inst);
	messenger_destroy(c->msgr, c->inst);
	instance_destroy(c->inst);

	log_info("The Core was Destroyed.");
}
