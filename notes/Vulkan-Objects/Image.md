# What is an Image?

The Image is just a set of pixels of special format, size, layers count, samples count and mip level in the GPU memory. The Image has usage flags; it can be a sampled image, a depth image, a color attachment, etc. It defines how the GPU should interact with this memory.

The Image characteristics:
- Format - format of the Image is a symbiosis of color channels and color depth. The color channel is the level of a particular color in an image.
And color depth is the number of bits allocated to each channel. The more bits, the more accurate the color reproduction.

- Size - size is Image width and height in pixels.

- Layer - layer is an element of an array of image slices. The image could be, for example, a cube map, with each slice representing one face of the cube.

- Mip Levels - mip levels are pre-created reduced copies of an image, where each subsequent copy is two times smaller in size.

# Dependencies

The Image depends on [Swapchain](Swapchain.md) because they are automatically created through it. Swapchain also manages 
image states: free, rendering, and presented.

# Links

- Vulkan Specification: **[Image](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#resources-images)**
- Vulkan Documentation: **[Image](https://docs.vulkan.org/refpages/latest/refpages/source/VkImage.html)**
