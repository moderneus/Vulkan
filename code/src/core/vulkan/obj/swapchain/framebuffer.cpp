#include "core/vulkan/obj/swapchain/framebuffer.hpp"
#include "core/vulkan/obj/swapchain/swapchain.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "core/vulkan/obj/renderpass/render_pass.hpp"
#include "core/vulkan/obj/image/depth_image.hpp"
#include "util/debug/log.hpp"

VkFramebufferCreateInfo framebuffer_create_info(const swapchain_state &st, const render_pass &rp, const std::array<VkImageView, 1> &atts)
{
	VkFramebufferCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	info.renderPass = rp.handle;
	info.attachmentCount = static_cast<uint32_t>(atts.size());
	info.pAttachments = atts.data();
	info.width = st.imgs[0].extent.width;
	info.height = st.imgs[0].extent.height;
	info.layers = 1;
	return info;
}

void framebuffers_create(swapchain_state *st, const device &dev, const render_pass &rp) 
{
	log_info("Creating a Framebuffers...");

	st->fbs.resize(st->views.size());

	for(uint32_t i = 0; i < st->views.size(); ++i) {
		std::array<VkImageView, 1> atts = {st->views[i].handle};
		VkFramebufferCreateInfo info = framebuffer_create_info(*st, rp, atts);

		if (vkCreateFramebuffer(dev.handle, &info, nullptr, &st->fbs[i]) != VK_SUCCESS)
			log_critical("Failed to Create the Framebuffers.");
	}

	log_info("The Framebuffers were Created.");
}

void framebuffers_destroy(const swapchain_state &st, const device &dev) 
{
	log_info("Destroying the Framebuffers...");

	for(const auto &fb : st.fbs)
		vkDestroyFramebuffer(dev.handle, fb, nullptr);

	log_info("The Framebuffers were Destroyed.");
}
