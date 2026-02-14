#include "core/vulkan/objects/swapchain/Framebuffer.hpp"
#include "core/vulkan/objects/swapchain/Swapchain.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "core/vulkan/objects/renderpass/RenderPass.hpp"
#include "util/debug/Logger.hpp"

VkFramebufferCreateInfo fb_create_info(const swapchain_state_t &st, const render_pass_t &rp, const VkImageView *atts) 
{
	VkFramebufferCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	info.renderPass = rp.handle;
	info.attachmentCount = 1;
	info.pAttachments = atts;
	info.width = st.extent.width;
	info.height = st.extent.height;
	info.layers = 1;
	return info;
}

void fbs_create(swapchain_state_t *st, const device_t &dev, const render_pass_t &rp) 
{
	log_info("Creating a Framebuffers...");

	st->fbs.resize(st->views.size());

	for(uint32_t i = 0; i < st->views.size(); ++i) {
		VkFramebufferCreateInfo info = fb_create_info(*st, rp, &st->views[i]);

		if (vkCreateFramebuffer(dev.handle, &info, nullptr, &st->fbs[i]) != VK_SUCCESS) {
			log_critical("Failed to Create the Framebuffers.");
		}
	}

	log_info("The Framebuffers were Created.");
}

void fbs_destroy(const swapchain_state_t &st, const device_t &dev) 
{
	log_info("Destroying the Framebuffers...");

	for(const auto &fb: st.fbs) {
		vkDestroyFramebuffer(dev.handle, fb, nullptr);
	}

	log_info("The Framebuffers were Destroyed.");
}
