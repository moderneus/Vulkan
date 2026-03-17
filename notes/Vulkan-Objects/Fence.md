# What is a Fence?

The Fence is a synchronization mechanism between host (CPU) and device (GPU) operations. It allows the host to wait for 
the device to finish and then continue. The Fence like a Semaphore comes in two states: idle and signal. For example:
the host cannot save a screenshot until the [Image](Image.md) is rendered.   

# Dependencies

The Fence directly depends on the [Device](Device.md) from which it is allocated. The Fence creates
dependencies itself between host and device operations.

# Links

- Vulkan Specification: **[Fence](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#synchronization-fences)**
- Vulkan Documentation: **[Fence](https://docs.vulkan.org/tutorial/latest/03_Drawing_a_triangle/03_Drawing/02_Rendering_and_presentation.html)**

