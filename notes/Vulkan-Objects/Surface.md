# What is a Surface?

The Surface is a Vulkan object that stores the context of the connected window system. In this case, the context is just a set of window handles. 
The Surface context allows the driver to determine the format, size, quantity, queues, and present modes. The Surface is part of the core WSI 
extension set because Vulkan is for rendering and not for presenting. If you want to present something to the screen, you must enable the 
necessary extensions. 

- **Format** – The pixel format and color space the presented images use.
- **Size** – The dimensions of the images that can be presented.
- **Quantity** – How many images can exist in the [Swapchain](Swapchain.md) simultaneously.
- **Queue** – Which queue families are allowed to present images to the surface.
- **Present Mode** – How image presentation is synchronized with the display system.

# Dependencies

The Surface depends on the [Instance](Instance.md) directly because it's an extension. Surface depends on the [PhysicalDevice](PhysicalDevice.md) 
since all of the support information must be compatible with the GPU. The [Swapchain](Swapchain.md) directly depends on the Surface because the 
present modes, formats and image extents are taken from it in conjunction with the GPU.

# Links

Vulkan Documentation: **[Surface](https://docs.vulkan.org/tutorial/latest/03_Drawing_a_triangle/01_Presentation/00_Window_surface.html)**

