#ifndef MOD_CORE_HPP
#define MOD_CORE_HPP

#include "core/vulkan/obj/instance/instance.hpp"
#include "core/vulkan/obj/instance/surface.hpp"
#include "core/vulkan/obj/debug/messenger.hpp"
#include "core/vulkan/obj/device/queue_indices.hpp"
#include "core/vulkan/obj/device/physical_device.hpp" 
#include "core/vulkan/obj/device/device.hpp"
#include "core/vulkan/obj/swapchain/swapchain.hpp"
#include "core/vulkan/obj/pipeline/pipeline_layout.hpp"
#include "core/vulkan/obj/buffer/vertex_buffer.hpp"
#include "core/vulkan/obj/buffer/index_buffer.hpp"
#include "core/vulkan/obj/buffer/uniform_buffer.hpp"
#include "core/vulkan/obj/descriptor/descriptor_set_layout.hpp"
#include "core/vulkan/obj/descriptor/descriptor_pool.hpp"
#include "core/vulkan/obj/descriptor/descriptor_set.hpp"
#include "core/vulkan/obj/image/depth_image.hpp"
#include "core/vulkan/obj/image/texture.hpp"
#include "core/vulkan/obj/image/image_view.hpp"
#include "core/vulkan/obj/image/sampler.hpp"
#include "core/vulkan/obj/pipeline/pipeline.hpp"
#include "core/vulkan/obj/renderpass/render_pass.hpp"
#include "core/vulkan/obj/command/command_pool.hpp"
#include "core/vulkan/obj/command/command_buffer.hpp"
#include "core/vulkan/obj/device/queue.hpp"
#include "core/vulkan/obj/sync/semaphore.hpp"
#include "core/vulkan/obj/sync/fence.hpp"

#include <vulkan/vulkan.h>

#include <vector>

struct window;

struct core {
	instance				inst;
	surface					surf;
	messenger				msgr;
	queue_indices				q_idx;
	queue					q;
	physical_device				gpu;
	device					dev;
	swapchain				swp;
	swapchain_state				swp_st;
	pipeline_layout				lyt;
	std::array<shader, 2>			shdrs;
	vertex_buffer				vert_buf = {{}, rectangles_verts};
	index_buffer				idx_buf = {{}, rectangles_indices};
	texture					tex;
	sampler					samp;
	depth_image				dp_img;
	std::vector<uniform_buffer>		uniform_bufs;
	descriptor_set_layout			set_lyt;
	descriptor_pool				set_pool;
	std::vector<descriptor_set>		sets;
	pipeline				pl;
	render_pass				rp;
	command_pool				cmd_pool;
	std::vector<command_buffer>		cmds;
	std::vector<semaphore>			img_avail_sems;
	std::vector<semaphore>			rnd_done_sems;
	std::vector<fence>			frm_fences;
};

void core_init(core *c, const window &win);

void core_destroy(core *c);

#endif
