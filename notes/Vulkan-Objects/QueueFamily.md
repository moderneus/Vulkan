# What is a QueueFamily?

The QueueFamily is a hardware-defined set of [Queues](Queue.md) with identical command execution capabilities. It can contain [Queues](Queue.md) optimized for specific 
commands: graphics, compute, transfer, and presentation. A [Queue](Queue.md) is a concrete hardware execution stream. Commands are submitted to a queue and executed 
on the GPU in sequence. Different [Queues](Queue.md) may execute in parallel.

# Dependencies

The QueueFamily depends on the [PhysicalDevice](PhysicalDevice.md) because its capabilities and the number of [Queues](Queue.md) are defined by the GPU. The choice of 
a QueueFamily determines which types of commands an application can submit efficiently. Specific [Queues](Queue.md), command execution, and task scheduling 
all depend on the selected QueueFamily. In turn, the [Device](Device.md) and command submission are constrained by the available queue families.

# Links

- Vulkan Specification: **[QueueFamily](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#devsandqueues-queues)**
- Vulkan Documentation: **[QueueFamily](https://docs.vulkan.org/guide/latest/queues.html)**
