# What is a Semaphore?

The Semaphore is a synchronization mechanism between the GPU operations. It allows you to create dependencies between queues to order the operations correctly. The Semaphores come in two states: idle and signal. The synchronized operation waits for a signal from the Semaphore to start executing. Once signaled, the Semaphore returns to the idle state. For example: the [Image](Image.md) cannot be presented until it is rendered. Rendering and presenting operations are performed by the GPU, so they must be synchronized with the Semaphores. 

# Dependencies

The Semaphore directly depends on the [Device](Device.md) from which it is allocated. The [Queues](Queue.md) take the Semaphore to know when they must be executed. Therefore the [Queue](Queue.md) starts to depend on the other [Queue](Queue.md). 

# Links

- Vulkan Specification: **[Semaphore](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#synchronization-semaphores)**
- Vulkan Documentation: **[Semaphore](https://docs.vulkan.org/tutorial/latest/03_Drawing_a_triangle/03_Drawing/02_Rendering_and_presentation.html)**