# What is a Device?

The Device is a Vulkan object that represents the interface through which the application interacts with the GPU. It manages memory allocations and resources.
The Device is based on a [PhysicalDevice](PhysicalDevice.md) and is created from it. The Device creation requires to specify which queues, features, extensions, 
and layers will be used.

# Dependencies

The Device depends on the [PhysicalDevice](PhysicalDevice.md) because Device is based on it. Many objects depend on the Device such as: [Queues](Queue.md), 
[CommandPools](CommandPool.md), [VertexBuffers](VertexBuffer.md), [Images](Image.md), [ImageViews](ImageView.md), [DescriptorSets](DescriptorSet.md), 
[Samplers](Sampler.md) and [Pipelines](Pipeline.md), as it manages the creation and lifetime of these resources.

# Links

- Vulkan Specification **[Device](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#devsandqueues-devices)**
- Vulkan Documentation **[Device](https://docs.vulkan.org/tutorial/latest/03_Drawing_a_triangle/00_Setup/04_Logical_device_and_queues.html)**
