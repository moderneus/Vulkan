#ifndef MOD_CORE_HPP
#define MOD_CORE_HPP

#include "core/vulkan/objects/instance/Instance.hpp"
#include "core/vulkan/objects/instance/Surface.hpp"
#include "core/vulkan/objects/debug/DebugMessenger.hpp"
#include "core/vulkan/objects/device/QueueFamily.hpp"
#include "core/vulkan/objects/device/PhysicalDevice.hpp" 
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "core/vulkan/objects/swapchain/Swapchain.hpp"
#include "core/vulkan/objects/pipeline/PipelineLayout.hpp"
#include "core/vulkan/objects/buffers/VertexBuffer.hpp"
#include "core/vulkan/objects/pipeline/Pipeline.hpp"
#include "core/vulkan/objects/renderpass/RenderPass.hpp"
#include "core/vulkan/objects/commands/CommandPool.hpp"
#include "core/vulkan/objects/commands/CommandBuffer.hpp"
#include "core/vulkan/objects/device/Queue.hpp"
#include "core/vulkan/objects/sync/Semaphore.hpp"
#include "core/vulkan/objects/sync/Fence.hpp"

#include <vulkan/vulkan.h>

#include <vector>

struct window_t;

struct core_t
{
	instance_t					inst;
	surface_t					surf;
	debug_msgr_t					msgr;
	queue_family_t					qf;
	queue_t						q;
	phys_device_t					phys_dev;
	device_t					dev;
	swapchain_t					swp;
	swapchain_state_t				swp_st;
	layout_t					layout;
	std::array<shader_t, 2>				shdrs;
	vertex_buffer_t					buf;
	vertex_buffer_mem_t				mem;
	pipeline_t					pl;
	render_pass_t					rp;
	command_pool_t					cmd_pool;
	std::vector<command_buffer_t>			cmd_bufs;
	std::vector<semaphore_t>			img_avail_sems;
	std::vector<semaphore_t>			rnd_done_sems;
	std::vector<fence_t>				frm_fences;
};

void core_init(core_t *core, const window_t &win);

void core_destroy(core_t *core);

#endif
