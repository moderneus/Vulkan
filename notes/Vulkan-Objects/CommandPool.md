# What is a CommandPool?

The CommandPool is a Vulkan object that allocates [CommandBuffers](CommandBuffer.md). From one CommandPool might be 
allocated many [CommandBuffers](CommandBuffer.md).

# Dependencies

The CommandPool depends on the [Device](Device.md) since it is allocated from it. The [CommandBuffer](CommandBuffer.md) directly depends on the CommandPool because it allocated from it.

# Links

- Vulkan Specification: **[CommandPool](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#commandbuffers-pools)**
- Vulkan Documentation: **[CommandPool](https://docs.vulkan.org/refpages/latest/refpages/source/VkCommandPool.html)**
