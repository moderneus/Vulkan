# What is a Queue?

A Queue is a hardware execution stream. The Queues are optimized for specific commands: graphics, compute, transfer, and presentation. Commands are submitted 
to a queue and executed on the GPU in sequence. Different Queues may execute in parallel.

# Dependencies

The Queue depends on the [Device](Device.md) since it selects what [QueueFamilies](QueueFamily.md) and [Queues](Queue.md) will be used.

# Links

- Vulkan Specification: [Queue](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#devsandqueues-queues)
- Vulkan Documentation: [Queue](https://docs.vulkan.org/guide/latest/queues.html)
