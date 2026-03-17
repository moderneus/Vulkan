# What is a RenderPass?

The RenderPass is a Vulkan object that describes the algorithm for data (attachments) flow in the GPU pipeline. In more detail,
the RenderPass tells the GPU what to do with the attachments at the beginning and end of RenderPass. The RenderPass also has 
the «Subpasses»; every «Subpass» is a concrete step in the RenderPass. The Subpass takes the specific attachment (attachment 
reference: color, depth/stencil, etc.), takes the bound [Pipeline](Pipeline.md) and performs operations. The Subpasses must
be synchronized by creating «dependencies» between them. 

# Dependencies

The rendering process depends on the RenderPass because it's enclosed in it. The [Framebuffers](Framebuffer.md) depend on the
RenderPass because Framebuffer is bound to the RenderPass and gives the attachments ([ImageViews](ImageView.md)). 
The [Pipeline](Pipeline.md) depends on the RenderPass directly because it compiled for the specific RenderPass.

# Links

- Vulkan Specification: **[RenderPass](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#renderpass)**
- Vulkan Documentation: **[RenderPass](https://docs.vulkan.org/spec/latest/chapters/renderpass.html)**
