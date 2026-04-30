#ifndef MOD_RENDER_PASS_HPP
#define MOD_RENDER_PASS_HPP

#include <vulkan/vulkan.h>

struct swapchain_state;
struct physical_device;
struct device;

#include <array>

struct render_pass {
	VkRenderPass handle = VK_NULL_HANDLE;
};

VkRenderPassBeginInfo render_pass_create_begin_info(const render_pass &rp, const swapchain_state &st, const std::array<VkClearValue, 2> &vals, uint32_t img_idx);

std::array<VkAttachmentDescription, 2> render_pass_create_att_descs(const swapchain_state &st, const physical_device &gpu);

VkAttachmentReference render_pass_create_color_att_ref();

VkAttachmentReference render_pass_create_depth_att_ref();

VkSubpassDescription render_pass_create_subp_desc(const VkAttachmentReference &col_ref, const VkAttachmentReference &dp_ref);

VkSubpassDependency render_pass_create_subp_dep();

VkRenderPassCreateInfo render_pass_create_info(const std::array<VkAttachmentDescription, 2> &atts, const VkSubpassDescription &subp, const VkSubpassDependency &dep);

void render_pass_create(render_pass *rp, const device &dev, const physical_device &gpu, const swapchain_state &st);

void render_pass_destroy(const render_pass &rp, const device &dev);

#endif
