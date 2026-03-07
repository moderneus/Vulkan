# What is a PipelineLayout?

The PipelineLayout is a Vulkan object that describes what [DescriptorSets](DescriptorSet.md) and push constants will be used. 
It allows the GPU to know how to access this memory and how to map it correctly. The [DescriptorSet](DescriptorSet.md) binding
requires the PipelineLayout.

# Dependencies

*The [DescriptorSets](DescriptorSet.md) and push constants can later be read by dispatch or draw calls, but only if the bound 
[Pipeline](Pipeline.md) being used for the command has a layout that is compatible with the layout that was used to bind the 
resources. Compatible means that the PipelineLayout must be the same object, or a different layout in which the push constant 
ranges and [DescriptorSet](DescriptorSet.md) layouts were be identically defined.* 

This excerpt was taken from this site because I don't know how to describe dependencies: 
[Vulkan Rust Documentation](https://docs.rs/vulkano/latest/vulkano/pipeline/layout/index.html)

# Links 

- Vulkan Specification: **[PipelineLayout](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#descriptors-pipelinelayout)**
- Vulkan Documentation: **[PipelineLayout](https://docs.vulkan.org/refpages/latest/refpages/source/VkPipelineLayout.html)**
