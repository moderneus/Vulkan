#ifndef MOD_CORE_HPP
#define MOD_CORE_HPP

#include "core/vulkan/obj/instance/instance.hpp"
#include "core/vulkan/obj/instance/surface.hpp"
#include "core/vulkan/obj/debug/messenger.hpp"
#include "core/vulkan/obj/device/queue_indices.hpp"
#include "core/vulkan/obj/device/physical_device.hpp" 
#include "core/vulkan/obj/device/device.hpp"
#include "core/vulkan/obj/swapchain/swapchain.hpp"
#include "core/vulkan/obj/pipeline/layout.hpp"
#include "core/vulkan/obj/buffers/vertex_buffer.hpp"
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

struct core
{
	instance				inst;
	surface					surf;
	messenger				msgr;
	queue_indices				q_idx;
	queue					q;
	physical_device				gpu;
	device					dev;
	swapchain				swp;
	swapchain_state				swp_st;
	layout					lyt;
	std::array<shader, 2>			shaders;
	vertex_buffer				buf;
	vertex_buffer_mem			mem;
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
