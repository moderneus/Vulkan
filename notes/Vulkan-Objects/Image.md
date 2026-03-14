# What is an Image?

The Image is just a set of pixels of special format, size, layers count and mip level in the GPU memory. The Image has usage flags; it can be a sampled image, a color attachment, etc. It defines how the GPU should interact with this memory.

# Dependencies

The Image depends on [Swapchain](Swapchain.md) because they are automatically created through it. Swapchain also manages 
image states: free, rendering, and presented.

# Links

- Vulkan Specification: **[Image](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#resources-images)**
- Vulkan Documentation: **[Image](https://docs.vulkan.org/refpages/latest/refpages/source/VkImage.html)**
