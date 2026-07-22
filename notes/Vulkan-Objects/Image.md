# What is an Image?

The Image is just a set of pixels of special format, size, layers count, samples count and mip level in the GPU memory. The Image has usage flags; it can be a sampled image, a depth image, a color attachment, etc. It defines how the GPU should interact with this memory.

## The Image main characteristics

- Format - format of the Image is a symbiosis of color channels and color depth. The color channel is the level of a particular color in an image.
And color depth is the number of bits allocated to each channel. The more bits, the more accurate the color reproduction.

- Size - size is Image width and height in pixels.

- Layer - layer is an element of an array of image slices. The image could be, for example, a cube map, with each slice representing one face of the cube.

- Mip Levels - mip levels are pre-created reduced copies of an image, where each subsequent copy is two times smaller in size.

- Samples Count - samples count is the number of sample points per pixel used during rasterization. The more samples per pixel, the more accurate the edge
reconstruction. Each sample can be thought of as a subpixel of each pixel.

## Image Types

- Color Image - A color image is an image for which the final color has been calculated for each pixel.

- Depth Image - A depth image is an image used as a buffer, storing a value between 0.0 and 1.0, representing the pixel's distance (think of it as an additional Z-axis
for each pixel). During rasterization, a depth check is performed: the depth value of each subsequent pixel is compared with the previous one. If it's less than or
equal, it's drawn; if it's greater, it's not. The depth value of the very first pixel is always compared to 1.0.

- Multisampled Image - A multisampled image is an image with an increased number of sample points per pixel. This allows for more accurate rasterization. This image is
later written to a single-sample image (Color Image) and displayed on the screen since the monitor has only one sample per pixel. To write a multi-sampled image to a
single-sampled image, the GPU performs a process called resolve—an averaging of the values ​​for each pixel. It takes all the samples (subpixels), adds their corresponding
color channels, and divides the result by the number of samples. 

# Dependencies

The Image depends on [Swapchain](Swapchain.md) because they are automatically created through it. Swapchain also manages 
image states: free, rendering, and presented.

# Links

- Vulkan Specification: **[Image](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#resources-images)**
- Vulkan Documentation: **[Image](https://docs.vulkan.org/refpages/latest/refpages/source/VkImage.html)**
