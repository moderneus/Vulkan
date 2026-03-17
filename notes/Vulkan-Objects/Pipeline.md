# What is a Pipeline?

The Pipeline is a Vulkan object that represents a set of stages in which the frame is rendered. Each Pipeline stage has an input data and an output data. The input data is usually the output of the previous stage.

# Dependencies

The Pipeline directly depends on the [Device](Device.md) from which it is allocated. The Pipeline is bound to a [RenderPass](RenderPass.md) since the [RenderPass](RenderPass.md) describes the environment in which the Pipeline will be used; this is necessary for the optimizations. The [ShaderModules](ShaderModule.md) are bound to the Pipeline since they will be executed in it. Also the [PipelineLayout](PipelineLayout.md) is needed to create the Pipeline because it
references to a set of [DescriptorLayouts](DescriptorSet.md) which will be used by shaders. 

# Links

- Vulkan Specification: **[Pipeline](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#pipelines-graphics)**
- Vulkan Documentation: **[Pipeline](https://docs.vulkan.org/spec/latest/chapters/pipelines.html)**