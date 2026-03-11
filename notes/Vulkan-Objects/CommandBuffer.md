# What is a CommandBuffer?

The CommandBuffer is a Vulkan object that stores the recorded commands to be submitted to the [Queue](Queue.md) for
execution. The CommandBuffers need to be synchronized with each other to prevent out-of-order command recording.

# Dependencies

The CommandBuffer directly depends on a [CommandPool](CommandPool.md) since it is allocated from it. What the queues 
will execute depends on the set of commands in the CommandBuffer.

# Links

- Vulkan Specification: **[CommandBuffer](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#commandbuffers)**
- Vulkan Documentation: **[CommandBuffer](https://docs.vulkan.org/tutorial/latest/03_Drawing_a_triangle/03_Drawing/01_Command_buffers.html)**
