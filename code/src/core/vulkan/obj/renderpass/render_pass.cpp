#include "core/vulkan/obj/renderpass/render_pass.hpp"
#include "core/vulkan/obj/swapchain/swapchain.hpp"
#include "core/vulkan/obj/device/device.hpp"
#include "core/vulkan/obj/image/depth_image.hpp"
#include "util/debug/log.hpp"

VkRenderPassBeginInfo render_pass_create_begin_info(const render_pass &rp, const swapchain_state &st, const std::array<VkClearValue, 2> &vals, uint32_t img_idx) 
{
	VkRenderPassBeginInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	info.renderPass = rp.handle;
	info.framebuffer = st.fbs[img_idx];
	info.renderArea.offset = {0, 0};
	info.renderArea.extent = st.imgs[0].extent;
	info.clearValueCount = static_cast<uint32_t>(vals.size());
	info.pClearValues = vals.data();
	return info;
}

std::array<VkAttachmentDescription, 1> render_pass_create_att_descs(const swapchain_state &st, const physical_device &gpu) 
{
	log_info("Creating an Attachment Description...");

	std::array<VkAttachmentDescription, 1> descs = {};

	descs[0].format = st.imgs[0].fmt;
	descs[0].samples = VK_SAMPLE_COUNT_1_BIT;
	descs[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	descs[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	descs[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	descs[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	descs[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	descs[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	log_info("The Attachment Description was Created.");

	return descs;
}

VkAttachmentReference render_pass_create_color_att_ref() 
{
	log_info("Creating the Attachment Reference...");

	VkAttachmentReference ref = {};
	ref.attachment = 0;
	ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	log_info("The Attachment Reference was Created.");

	return ref;
}

VkAttachmentReference render_pass_create_depth_att_ref() 
{
	VkAttachmentReference ref = {};
	ref.attachment = 1;
	ref.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	return ref;
}

VkSubpassDescription render_pass_create_subp_desc(const VkAttachmentReference &col_ref) 
{
	log_info("Creating a Subpass Description...");

	VkSubpassDescription desc = {};
	desc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	desc.colorAttachmentCount = 1;
	desc.pColorAttachments = &col_ref;

	log_info("The Subpasss Description was Created.");

	return desc;
}

VkSubpassDependency render_pass_create_subp_dep() 
{
	VkSubpassDependency dep = {};
	dep.srcSubpass = VK_SUBPASS_EXTERNAL;
	dep.dstSubpass = 0;
	dep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
	dep.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
	dep.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
	dep.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
	return dep;
}

VkRenderPassCreateInfo render_pass_create_info(const std::array<VkAttachmentDescription, 1> &atts, const VkSubpassDescription &subp, const VkSubpassDependency &dep) 
{
	log_info("Creating the Render Pass Info...");

	VkRenderPassCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	info.attachmentCount = static_cast<uint32_t>(atts.size());
	info.pAttachments = atts.data();
	info.subpassCount = 1;
	info.pSubpasses = &subp;
	info.dependencyCount = 1;
	info.pDependencies = &dep;

	log_info("The Render Pass Info was Created.");

	return info;
}

void render_pass_create(render_pass *rp, const device &dev, const physical_device &gpu, const swapchain_state &st) 
{
	log_info("Creating a Render Pass...");

	std::array<VkAttachmentDescription, 1> atts = render_pass_create_att_descs(st, gpu);
	VkAttachmentReference col_ref = render_pass_create_color_att_ref();
	VkSubpassDescription subp = render_pass_create_subp_desc(col_ref);
	VkSubpassDependency dep = render_pass_create_subp_dep();
	VkRenderPassCreateInfo info = render_pass_create_info(atts, subp, dep);

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
