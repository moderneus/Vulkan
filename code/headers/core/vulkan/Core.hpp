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
	instance_t				instance;
	surface_t				surface;
	debug_msgr_t				debug_msgr;
	queue_family_t				queue_family;
	queue_t					queue;
	phys_device_t				phys_device;
	device_t				device;
	swapchain_t				swapchain;
	swapchain_state_t			swapchain_state;
	pipeline_layout_t			pipeline_layout;
	std::array<shader_module_t, 2>		shader_modules;
	pipeline_t				pipeline;
	render_pass_t				render_pass;
	command_pool_t				command_pool;
	std::vector<command_buffer_t>		command_buffers;
	std::vector<semaphore_t>		img_available_semaphores;
	std::vector<semaphore_t>		render_finished_semaphores;
	std::vector<fence_t>			in_flight_fences;
};

void vk_core_init(core_t* vk_core, const window_t& window);

void vk_core_destroy(core_t* vk_core);

#endif
