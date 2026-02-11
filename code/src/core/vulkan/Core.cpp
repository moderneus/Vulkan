#include "core/vulkan/Core.hpp"
#include "core/vulkan/objects/swapchain/ImageView.hpp"
#include "core/vulkan/objects/swapchain/Framebuffer.hpp"
#include "util/debug/Logger.hpp"

void core_init(core_t *core, const window_t &win) 
{
	log_info("Initializing a Core...");

	inst_create(&core->inst);
	dbg_msgr_setup(&core->msgr, core->inst);
	surf_create(&core->surf, core->inst, win);
	phys_dev_pick(&core->phys_dev, core->inst, core->surf);
	qf_find(&core->qf, core->phys_dev, core->surf);
	dev_create(&core->dev, &core->q, core->qf, core->phys_dev);
	swp_create(&core->swp, &core->swp_st, core->dev, core->phys_dev, core->qf, core->surf, win);
	img_views_create(&core->swp_st, core->dev);
	layout_create(&core->layout, core->dev);
	rp_create(&core->rp, core->dev, core->swp_st);
	shdrs_create(&core->shdrs, core->dev);
	vert_buf_create(&core->buf, &core->mem, core->dev, core->phys_dev);
	pl_create(&core->pl, core->dev, core->layout, core->rp, core->swp_st, core->shdrs);
	fbs_create(&core->swp_st, core->dev, core->rp);
	cmd_pool_create(&core->cmd_pool, core->dev, core->qf);
	cmd_bufs_create(&core->cmd_bufs, core->dev, core->cmd_pool);
	sems_create(&core->img_avail_sems, core->dev);
	sems_create(&core->rnd_done_sems, core->dev);
	fences_create(&core->frm_fences, core->dev);

	log_info("The Core was Initialized."); 
}

void core_destroy(core_t* core) 
{
	log_info("Destroying the Core...");

	fences_destroy(core->frm_fences, core->dev);
	sems_destroy(core->rnd_done_sems, core->dev);
	sems_destroy(core->img_avail_sems, core->dev);
	cmd_pool_destroy(core->cmd_pool, core->dev);
	fbs_destroy(core->swp_st, core->dev);
	pl_destroy(core->pl, core->dev);
	vert_buf_destroy(core->buf, core->mem, core->dev);
	shdrs_destroy(core->shdrs, core->dev);
	rp_destroy(core->rp, core->dev);
	layout_destroy(core->layout, core->dev);
	img_views_destroy(core->swp_st, core->dev);
	swp_destroy(core->swp, core->dev);
	dev_destroy(core->dev);
	surf_destroy(core->surf, core->inst);
	dbg_msgr_destroy(core->msgr, core->inst);
	inst_destroy(core->inst);

	log_info("The Core was Destroyed.");
}
