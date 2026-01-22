# What is a Swapchain?

The Swapchain is a Vulkan object that represents a set of images with a fixed format and size, organized as a queue that manages rendering and presentation of frames through a selected presentation mode. The swapchain itself decides which image is used for rendering, which image is queued for presentation, and which image is currently being displayed. During rendering, the application only needs to acquire an available image and submit the rendering commands to the graphics queue. The swapchain is part of WSI: Vulkan handles rendering, not presentation.

# How to create?

# How to destroy?

# Dependencies

The Swapchain depends on the Surface, the PhysicalDevice capabilities (supported formats, present modes, image count), and queues that support presentation. Based on the Swapchain, its Images, ImageViews, and corresponding Framebuffers are created. The Swapchain’s format and extent define the RenderPasses and all attachments used for on-screen rendering. When the Surface changes or becomes incompatible, the Swapchain and all dependent Vulkan objects must be recreated.

# Links

- Vulkan Documentation **[Swapchain](https://docs.vulkan.org/tutorial/latest/03_Drawing_a_triangle/01_Presentation/01_Swap_chain.html)**