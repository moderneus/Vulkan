#ifndef MOD_RENDER_PASS_HPP
#define MOD_RENDER_PASS_HPP

#include <vulkan/vulkan.h>

struct swapchain_state;
struct device;

struct render_pass {
	VkRenderPass handle = VK_NULL_HANDLE;
};

VkRenderPassBeginInfo render_pass_create_begin_info(const render_pass &rp, const swapchain_state &st, const VkClearValue &col, uint32_t img_idx);

VkAttachmentDescription render_pass_create_att_desc(const swapchain_state &st);

VkAttachmentReference render_pass_create_att_ref();

VkSubpassDescription render_pass_create_subp_desc(const VkAttachmentReference &ref);

VkSubpassDependency render_pass_create_subp_dep();

VkRenderPassCreateInfo render_pass_create_info(const VkAttachmentDescription &att, const VkSubpassDescription &subp, const VkSubpassDependency &dep);

void render_pass_create(render_pass *rp, const device &dev, const swapchain_state &st);
    
void render_pass_destroy(const render_pass &rp, const device &dev);

#endif
