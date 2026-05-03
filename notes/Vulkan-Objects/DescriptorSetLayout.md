# What is a DescriptorSetLayout?

The DescriptorSetLayout is a Vulkan object that represents the array of the [DescriptorSet](DescriptorSet.md) bindings.
The DescriptorSetLayout defines the binding number of each [DescriptorSet](DescriptorSet.md), the type of each 
[DescriptorSet](DescriptorSet.md) and the shader stages in which they'll be used.

# Dependencies

The DescriptorSetLayouts are passed to the [PipelineLayout](PipelineLayout.md) for the compatibility between the
[Pipeline](Pipeline.md) and shaders in it.

# Links

- Vulkan Specification: [DescriptorSetLayout](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#descriptors-setlayout)
- Vulkan Documentation: [DescriptorSetLayout](https://docs.vulkan.org/spec/latest/chapters/descriptorsets.html#descriptors-setlayout)
