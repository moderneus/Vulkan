#include "core/vulkan/objects/renderpass/RenderPass.hpp"
#include "core/vulkan/objects/swapchain/Swapchain.hpp"
#include "core/vulkan/objects/device/LogicalDevice.hpp"
#include "util/debug/Logger.hpp"

VkRenderPassBeginInfo rp_create_begin_info(const render_pass_t &rp, const swapchain_state_t& st, uint32_t img_idx, const VkClearValue clear_col) 
{
	VkRenderPassBeginInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	info.renderPass = rp.handle;
	info.framebuffer = st.frame_buffers[img_idx];
	info.renderArea.offset = {0, 0};
	info.renderArea.extent = st.extent;
	info.clearValueCount = 1;
	info.pClearValues = &clear_col;
	return info;
}

VkAttachmentDescription rp_create_att_desc(const swapchain_state_t &st) 
{
	log_info("Creating an Attachment Description...");

	VkAttachmentDescription desc = {};
	desc.format = st.format;
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

VkAttachmentReference rp_create_att_ref() 
{
	log_info("Creating the Attachment Reference...");

	VkAttachmentReference ref = {};
	ref.attachment = 0;
	ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	log_info("The Attachment Reference was Created.");

	return ref;
}

VkSubpassDescription rp_create_subp_desc(VkAttachmentReference *ref) 
{
	log_info("Creating a Subpass Description...");

	VkSubpassDescription desc = {};
	desc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	desc.colorAttachmentCount = 1;
	desc.pColorAttachments = ref;

	log_info("The Subpasss Description was Created.");

	return desc;
}

VkSubpassDependency rp_create_subp_dep() 
{
	VkSubpassDependency dep = {};
	dep.srcSubpass = VK_SUBPASS_EXTERNAL;
	dep.dstSubpass = 0;
	dep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dep.srcAccessMask = 0;
	dp.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dp.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	return dp;
}

VkRenderPassCreateInfo rp_create_info(VkAttachmentDescription *att, VkSubpassDescription *subp, VkSubpassDependency *dep) 
{
	log_info("Creating the Render Pass Info...");

	VkRenderPassCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	info.attachmentCount = 1;
	info.pAttachments = att;
	info.subpassCount = 1;
	info.pSubpasses = subp;
	info.dependencyCount = 1;
	info.pDependencies = dep;

	log_info("The Render Pass Info was Created.");

	return info;
}

void rp_create(render_pass_t *rp, const device_t &dev, const swapchain_state_t& st) 
{
	log_info("Creating a Render Pass...");

	VkAttachmentDescription att_desc = rp_create_att_desc(st);
	VkAttachmentReference att_ref = rp_create_att_ref();
	VkSubpassDescription subp = rp_create_subp_desc(&att_ref);
	VkSubpassDependency subp_dep = rp_create_subp_dep();
	VkRenderPassCreateInfo info = rp_create_info(&att_desc, &subp, &subp_dep);

	if (vkCreateRenderPass(dev.handle, &info, nullptr, &rp->handle) != VK_SUCCESS) {
		log_critical("Failed to Create the Render Pass.");
	}

	log_info("The Render Pass was Created.");
}

void render_pass_destroy(const render_pass_t &rp, const device_t &dev) 
{
	log_info("Destroying the Render Pass...");

	if (rp.handle == VK_NULL_HANDLE) {
		log_error("Cannot Destroy the Render Pass::Render Pass is not Created.");
	}

	vkDestroyRenderPass(dev.handle, rp.handle, nullptr);

	log_info("The Render Pass was Destroyed.");
}
