#ifndef MOD_RENDER_PASS_HPP
#define MOD_RENDER_PASS_HPP

#include <vulkan/vulkan.h>

struct swapchain_state_t;
struct device_t;

struct render_pass_t 
{
	VkRenderPass handle = VK_NULL_HANDLE;
};

VkRenderPassBeginInfo render_pass_create_begin_info(const render_pass_t& render_pass, const swapchain_state_t& st, uint32_t img_idx, const VkClearValue clear_color);

VkAttachmentDescription render_pass_create_attachment_description(const swapchain_state_t& st);

VkAttachmentReference render_pass_create_attachment_reference();

VkSubpassDescription render_pass_create_subpass_description(VkAttachmentReference* pattachment_ref);

VkSubpassDependency render_pass_create_subpass_dependency();

VkRenderPassCreateInfo render_pass_create_info(VkAttachmentDescription* pattachemnt_description, VkSubpassDescription* psubpass, VkSubpassDependency* subpass_dependency);

void render_pass_create(render_pass_t* render_pass, const device_t& device, const swapchain_state_t& st);
    
void render_pass_destroy(render_pass_t* render_pass, const device_t& device);

#endif
