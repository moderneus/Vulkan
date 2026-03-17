# What is a Buffer?

The Buffer is a Vulkan object that represents a linear arrays of data for special puproses. The Buffer binds to the [Pipeline](Pipeline.md)
via [DescriptorSet](DescriptorSet.md) and provides the data stored in this Buffer.

# Dependencies

The Buffer directly depends on the [Device](Device.md) from which it allocated. The Buffer is bound to the [Pipeline](Pipeline.md) via 
[DescriptorSet](DescriptorSet.md). 

# Links

- Vulkan Specification: **[Buffer](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#resources-buffers)**
- Vulkan Documentation: **[Buffer](https://docs.vulkan.org/tutorial/latest/04_Vertex_buffers/01_Vertex_buffer_creation.html)**
