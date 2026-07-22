# What is a Swapchain?

The Swapchain is a Vulkan object that represents a set of [Images](Image.md) with a fixed format and size, organized as a queue that manages rendering 
and presentation of frames through a selected presentation mode. The swapchain itself decides which [Image](Image.md) is used for rendering, which 
[Image](Image.md) is queued for presentation, and which [Image](Image.md) is currently being displayed. During rendering, the application only needs to acquire an 
available [Image](Image.md) and submit the rendering commands to the graphics queue. The swapchain is part of WSI: Vulkan handles rendering, not presentation.

The Present Modes:

- **FIFO** — Images are displayed strictly one after another. All [Images](Image.md) will be displayed, but if the [Image](Image.md) queue is full, the graphics device is
  forced to wait.
- **MAILBOX** — This is the same FIFO, but with frame replacement if the graphics device is running too fast. If, when displaying an [Image](Image.md), others
  are already outdated, they are replaced with current ones.
- **FIFO_RELAXED** — This is also the same as FIFO, however, frames are still sometimes replaced so as not to block the graphics device too much.

# Dependencies

Swapchain depends on the [Surface](Surface.md) since all of the support information is taken from it. The [Images](Image.md) depend on the Swapchain because it manages their state.

# Links

- Vulkan Documentation **[Swapchain](https://docs.vulkan.org/tutorial/latest/03_Drawing_a_triangle/01_Presentation/01_Swap_chain.html)**
