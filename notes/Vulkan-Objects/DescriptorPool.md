# What is a DescriptorPool? 

The DescriptorPool is a Vulkan Object that allocates [DescriptorSets](DescriptorSet.md). From one
DescriptorPool might be allocated many [DescriptorSets](DescriptorSet.md).

# Dependencies

The DescriptorPool depends on the [Device](Device.md) since it allocated from it. And the
[DescriptorSets](DescriptorSet.md) directly depends on the DescriptorPool because it 
allocated from it.

# Links

- Vulkan Specification: **[DescriptorPool]()**
- Vulkan Documentation: **[DescriptorPool]()**
