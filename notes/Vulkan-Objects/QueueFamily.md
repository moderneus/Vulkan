# What is a QueueFamily?

The QueueFamily is a hardware-defined set of [Queues](Queue.md) with identical command execution capabilities. 

# Dependencies

The QueueFamily depends on the [PhysicalDevice](PhysicalDevice.md) because its capabilities and the number of [Queues](Queue.md) are defined by the GPU. The choice of 
a QueueFamily determines which types of commands an application can submit efficiently. Specific [Queues](Queue.md), command execution, and task scheduling 
all depend on the selected QueueFamily. In turn, the [Device](Device.md) and command submission are constrained by the available queue families.

# Links

- Vulkan Specification: **[QueueFamily](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#devsandqueues-queues)**
- Vulkan Documentation: **[QueueFamily](https://docs.vulkan.org/guide/latest/queues.html)**
