# What is a Fence?

The Fence is a synchronization mechanism between CPU and GPU operations. It allows the CPU wait before 
the GPU ends and than continue. The Fence as a Semaphore come in two states: idle and signal. For example:
the CPU cannot save a screenshot until the [Image](Image.md) is rendered.   

# Dependencies

The Fence directly depends on the [Device](Device.md) which from it is allocated. The Fence creates
dependencies itself between CPU and GPU operations.

# Links

- Vulkan Specification: **[Fence](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#synchronization-fences)**
- Vulkan Documentation: **[Fence](https://docs.vulkan.org/tutorial/latest/03_Drawing_a_triangle/03_Drawing/02_Rendering_and_presentation.html)**
