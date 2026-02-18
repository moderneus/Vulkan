#include "core/vulkan/obj/renderpass/render_pass.hpp"
#include "core/vulkan/obj/swapchain/swapchain.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "util/debug/log.hpp"

VkRenderPassBeginInfo render_pass_create_begin_info(const render_pass &rp, const swapchain_state &st, const VkClearValue &clear_col, uint32_t img_idx) 
{
	VkRenderPassBeginInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	info.renderPass = rp.handle;
	info.framebuffer = st.fbs[img_idx];
	info.renderArea.offset = {0, 0};
	info.renderArea.extent = st.extent;
	info.clearValueCount = 1;
	info.pClearValues = &clear_col;
	return info;
}

VkAttachmentDescription render_pass_create_att_desc(const swapchain_state &st) 
{
	log_info("Creating an Attachment Description...");

	VkAttachmentDescription desc = {};
	desc.format = st.fmt;
	desc.samples = VK_SAMPLE_COUNT_1_BIT;
	desc.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	desc.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	desc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	desc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	desc.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	desc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	log_info("The Attachment Description was Created.");

	return desc;
}

VkAttachmentReference render_pass_create_att_ref() 
{
	log_info("Creating the Attachment Reference...");

	VkAttachmentReference ref = {};
	ref.attachment = 0;
	ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	log_info("The Attachment Reference was Created.");

	return ref;
}

VkSubpassDescription render_pass_create_subp_desc(const VkAttachmentReference &ref) 
{
	log_info("Creating a Subpass Description...");

	VkSubpassDescription desc = {};
	desc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	desc.colorAttachmentCount = 1;
	desc.pColorAttachments = &ref;

	log_info("The Subpasss Description was Created.");

	return desc;
}

VkSubpassDependency render_pass_create_subp_dep() 
{
	VkSubpassDependency dep = {};
	dep.srcSubpass = VK_SUBPASS_EXTERNAL;
	dep.dstSubpass = 0;
	dep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dep.srcAccessMask = 0;
	dep.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dep.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	return dep;
}

VkRenderPassCreateInfo render_pass_create_info(const VkAttachmentDescription &att, const VkSubpassDescription &subp, const VkSubpassDependency &dep) 
{
	log_info("Creating the Render Pass Info...");

	VkRenderPassCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	info.attachmentCount = 1;
	info.pAttachments = &att;
	info.subpassCount = 1;
	info.pSubpasses = &subp;
	info.dependencyCount = 1;
	info.pDependencies = &dep;

	log_info("The Render Pass Info was Created.");

	return info;
}

void render_pass_create(render_pass *rp, const device &dev, const swapchain_state &st) 
{
	log_info("Creating a Render Pass...");

	VkAttachmentDescription desc = render_pass_create_att_desc(st);
	VkAttachmentReference ref = render_pass_create_att_ref();
	VkSubpassDescription subp = render_pass_create_subp_desc(ref);
	VkSubpassDependency dep = render_pass_create_subp_dep();
	VkRenderPassCreateInfo info = render_pass_create_info(desc, subp, dep);

	if (vkCreateRenderPass(dev.handle, &info, nullptr, &rp->handle) != VK_SUCCESS)
		log_critical("Failed to Create the Render Pass.");

	log_info("The Render Pass was Created.");
}

void render_pass_destroy(const render_pass &rp, const device &dev) 
{
	log_info("Destroying the Render Pass...");

	if (rp.handle == VK_NULL_HANDLE)
		log_error("Cannot Destroy the Render Pass::Render Pass is not Created.");

	vkDestroyRenderPass(dev.handle, rp.handle, nullptr);

	log_info("The Render Pass was Destroyed.");
}
