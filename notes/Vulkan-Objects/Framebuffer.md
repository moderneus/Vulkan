# What is a Framebuffer?

The Framebuffer is a Vulkan object that contains a set of [ImageViews](ImageView.md). The Framebuffer is created for a 
compatible RenderPass and provides the attachments. Usually, the Framebuffer represents one frame.

# Dependencies

The Framebuffer depends on RenderPass because it's created relative to it. The Framebuffer often depends on the 
[Swapchain](Swapchain.md) because it provides the [Image](Image.md) extents. The Framebuffer also defines the 
render area size. So, if the [Image](Image.md) size changes, then Framebuffer must be recreated.

# Links

- Vulkan Specification: **[Framebuffer](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#_framebuffers)**
- Vulkan Documentation: **[Framebuffer](https://docs.vulkan.org/refpages/latest/refpages/source/VkFramebuffer.html)**
