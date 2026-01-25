#include "core/vulkan/objects/swapchain/Framebuffer.hpp"
#include "core/vulkan/objects/swapchain/Swapchain.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "core/vulkan/objects/renderpass/RenderPass.hpp"
#include "util/debug/Logger.hpp"

VkFramebufferCreateInfo framebuffer_create_info(const swapchain_config_t& cfg, const render_pass_t& render_pass, const VkImageView* attachments) 
{
	VkFramebufferCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	create_info.renderPass = render_pass.handle;
	create_info.attachmentCount = 1;
	create_info.pAttachments = attachments;
	create_info.width = cfg.extent.width;
	create_info.height = cfg.extent.height;
	create_info.layers = 1;
	return create_info;
}

void framebuffers_create(swapchain_config_t* cfg, const device_t& device, const render_pass_t& render_pass) 
{
	log_info("Creating a Framebuffers...");

	cfg->frame_buffers.resize(cfg->views.size());

	for(uint32_t i = 0; i < cfg->views.size(); ++i) {
		VkFramebufferCreateInfo framebuffer_info = framebuffer_create_info(*cfg, render_pass, &cfg->views[i]);

		if (vkCreateFramebuffer(device.handle, &framebuffer_info, nullptr, &cfg->frame_buffers[i]) != VK_SUCCESS) {
			log_critical("Failed to Create the Framebuffers.");
		}
	}

	log_info("The Framebuffers were Created.");
}

void framebuffers_destroy(const swapchain_config_t& cfg, const device_t& device) 
{
	log_info("Destroying the Framebuffers...");

	for(const auto& framebuffer : cfg.frame_buffers) {
		vkDestroyFramebuffer(device.handle, framebuffer, nullptr);
	}

	log_info("The Framebuffers were Destroyed.");
}
