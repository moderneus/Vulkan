# What is an ImageView?

The ImageView is a Vulkan object that represents an interpretation of the [Image](Image.md). «View» means *take the specified Image part*: layer, view type, mip level. 
And also convert if possible to specified format and components. During ImageView creation the format, view type, components, layers and mip levels must be specified.

# Dependencies

The ImageView determines how shaders in the [Pipeline](Pipeline.md) will see and work with the image.

# Links

- Vulkan Specification: **[ImageView](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#resources-image-views)**
- Vulkan Documentation: **[ImageView](https://docs.vulkan.org/tutorial/latest/03_Drawing_a_triangle/01_Presentation/02_Image_views.html)**

