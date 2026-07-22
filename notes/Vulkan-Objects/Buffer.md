# What is a Buffer?

The Buffer is a Vulkan object that represents the linear arrays of data for special puproses. The Buffer binds to the [Pipeline](Pipeline.md)
via [DescriptorSet](DescriptorSet.md) and provides the data stored in this Buffer.

## Buffer types

- Vertex Buffer - buffer that stores vertices. Each vertex consists of typically three
attributes: position, color, texture coordinate. They bind using the
*vkCmdBindVertexBuffers* command.

- Index Buffer - buffer that stores indices of vertices. Each index points to
specific vertex to avoid duplication. They bind using the *vkCmdBindIndexBuffer*
command.

- Uniform Buffer - buffer that stores some values used in shaders. They should be
updated if the values are dynamic. They bind using the [DescriptorSet](DescriptorSet.md)
via *vkCmdBindDescriptorSets*.

- Staging Buffer - temporary buffer used to transfer data to the actual buffer. We need
them to create buffer in [Device](Device.md) local memory space. Since the [Device](Device.md)
local memory space cannot be mapped and freely used by the CPU. To copy data from the staging
buffer use the *vkCmdCopyBuffer* command.

- Shader Storage Buffer - buffer that is used by shaders to read or write into them. They
bind using the [DescriptorSet](DescriptorSet.md) via *vkCmdBindDescriptorSets*.

# Dependencies

The Buffer directly depends on the [Device](Device.md) from which it allocated. The Buffer is bound to the [Pipeline](Pipeline.md) via 
[DescriptorSet](DescriptorSet.md). 

# Links

- Vulkan Specification: **[Buffer](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#resources-buffers)**
- Vulkan Documentation: **[Buffer](https://docs.vulkan.org/tutorial/latest/04_Vertex_buffers/01_Vertex_buffer_creation.html)**
