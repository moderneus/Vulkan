# What is a ShaderModule?

The ShaderModule is a Vulkan object that represents a shader code wrapper. The code of the shader has to be compiled and placed 
into info-structure in binary form. The ShaderModule is bound to the [Pipeline](Pipeline.md) with a special stage-flag. The 
stage-flag tells the GPU what kind of shader it is: vertex shader, fragment shader, geometry shader, etc.

# Dependencies

The ShaderModule depends on the [Device](Device.md) since it is allocated from it. The ShaderModule is bound to the 
[Pipeline](Pipeline.md), without it the ShaderModule doesn't make sense.

# Links

- Vulkan Specification: **[ShaderModule](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#shader-modules)**
- Vulkan Documentation: **[ShaderModule](https://docs.vulkan.org/refpages/latest/refpages/source/VkShaderModule.html)**
