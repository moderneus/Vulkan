#ifndef MOD_RENDER_PASS_HPP
#define MOD_RENDER_PASS_HPP

#include <vulkan/vulkan.h>

struct swapchain_state_t;
struct device_t;

struct render_pass_t 
{
	VkRenderPass handle = VK_NULL_HANDLE;
};

VkRenderPassBeginInfo rp_create_begin_info(const render_pass_t &rp, const swapchain_state_t& st, uint32_t img_idx, const VkClearValue col);

VkAttachmentDescription rp_create_att_desc(const swapchain_state_t& st);

VkAttachmentReference rp_create_att_ref();

VkSubpassDescription rp_create_subp_desc(VkAttachmentReference *ref);

VkSubpassDependency rp_create_subp_dep();

VkRenderPassCreateInfo rp_create_info(VkAttachmentDescription *att, VkSubpassDescription *subp, VkSubpassDependency *dep);

void rp_create(render_pass_t *rp, const device_t &dev, const swapchain_state_t &st);
    
void rp_destroy(const render_pass_t &rp, const device_t &dev);

#endif
