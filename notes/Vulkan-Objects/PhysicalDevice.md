# What is a PhysicalDevice?

The PhysicalDevice is a Vulkan object that represents a specific GPU available on the system. It is a purely informational object describing 
the device’s features, limits, and available [QueueFamilies](QueueFamily.md). It doesn't manage resources, allocate memory, or participate in 
command execution. 

# Dependencies

The PhysicalDevice is created after the [Instance](Instance.md) and depends only on it, as the Vulkan instance determines which physical 
devices are available on the system. It has no mutable state and does not depend on any [Device](Device.md) or resources. The creation of a 
[Device](Device.md) directly depends on the PhysicalDevice, since it defines the available [Queues](Queue.md), features, limits, and extensions. 
All Vulkan resources and operations ultimately rely on the selected PhysicalDevice through the corresponding Device.

# Links

- Vulkan Specification: **[PhysicalDevice](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#devsandqueues-physical-device-enumeration)**
- Vulkan Documentation: **[PhysicalDevice](https://docs.vulkan.org/spec/latest/chapters/devsandqueues.html)**
