# What is a DescriptorSet?

The DescriptorSet is a Vulkan object that represents a memory space for descriptors. Each descriptor is a resource with a specific type
defined in a [DescriptorSetLayout](DescriptorSetLayout.md). The DescriptorSets are mostly used by shaders to get an access to the 
resources in them. The DescriptorSets are bound using special command (vkCmdBindDescriptorSets) and can be used in the specified
shader stages.

# Dependencies

The DescriptorSets are allocated from the [DescriptorPool](DescriptorPool.md). The binding number, type and a shader stage they'll of the
DescriptorSets are defined by [DescriptorSetLayout](DescriptorSetLayout.md). To bind the DescriptorSets the [PipelineLayout](PipelineLayout.md) 
must be passed in the relevant command since the DescriptorSets are used by shaders in the determined binding number. 

# Links

- Vulkan Specification: **[DescriptorSet](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#descriptors-sets)**
- Vulkan Documentation: **[DescriptorSet](https://docs.vulkan.org/spec/latest/chapters/descriptorsets.html#descriptors-setlayout)**
