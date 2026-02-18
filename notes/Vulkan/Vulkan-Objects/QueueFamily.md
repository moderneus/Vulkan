# What is a QueueFamily?

A queue family is a hardware-defined set of queues with identical command execution capabilities. It can contain queues optimized for specific commands: graphics, compute, transfer, and presentation. A queue is a concrete hardware execution stream. Commands are submitted to a queue and executed on the GPU in sequence. Different queues may execute in parallel.

# How to find the QueueFamily?

Before we search for the queues we need: graphics and present. Each queue family has its own index: 0, 1, 2, etc. We'll create a structure to conveniently store them. 
We made them optional so that we could easily check whether the indices of these families were found.

```cpp
struct QueueFamily
{
    std::optional<uint32_t> graphics; // index of the queue family that supports graphics commands
    std::optional<uint32_t> present;  // index of the queue family that supports presentation to the surface
};
```

First, we query the number of queue families, then place the characteristics of these queues into a vector. 
Each queue family has a bitmask, for example, *VK_QUEUE_GRAPHICS_BIT*. This bitmask lets us know whether a graphics queue is in this family.
In the loop, we go through all the families and when we find the desired family, we assign them an index or iteration number. Keep in mind that Vulkan is for rendering and doesn't have native presentation support. 
So, we must enable the Surface extension to determine whether our graphics device supports presentation in a specific queue family.

```cpp
void queue_family_find(QueueFamily* queue_family, const PhysicalDevice& phys_device, const Surface& surface)
{
    uint32_t queue_family_count = 0;

    // First, query how many queue families exist on this physical device
    vkGetPhysicalDeviceQueueFamilyProperties(phys_device.handle, &queue_family_count, nullptr);
    
    // Create a vector to store the properties of each queue family
    std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
    
    // Get the properties for all queue families
    vkGetPhysicalDeviceQueueFamilyProperties(phys_device.handle, &queue_family_count, queue_families.data());

    // Loop through all queue families
    for (uint32_t i = 0; i < queue_family_count; ++i)
    {
        // Check if this queue family supports graphics commands
        if(queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) 
            queue_family->graphics = i;
        
        // Check if this queue family supports presentation to the given surface
        VkBool32 present_support = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(phys_device.handle, i, surface.handle, &present_support);
        
        if(present_support) 
            queue_family->present = i;
        
        // If we found both graphics and presentation families, we can stop searching
        if(queue_family_is_complete(*queue_family)) 
            break;    
    }

    // If no suitable queue families were found, log a critical error
    if(!queue_family_is_complete(*queue_family)) 
        log_critical("Failed to Find any Suitable Queue Families!");
}
```

Here we simply return true if we found the indices of the required families.

```cpp
bool queue_family_is_complete(const QueueFamily& queue_family)
{
    // Return true if both graphics and presentation queue family indices are found
    return queue_family.graphics.has_value() && queue_family.present.has_value();
}
```

# Dependencies

A queue family depends on the physical device, because its capabilities and the number of queues are defined by the GPU hardware. The choice of a queue family determines which types of commands an application can submit efficiently. Specific queues, command execution, and task scheduling all depend on the selected queue family. In turn, the logical device and command submission are constrained by the available queue families.

# How to destroy?

Queue families and queues are managed by the GPU; you don’t create or destroy them manually.

# Links

- Vulkan Specification: **[QueueFamily](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#devsandqueues-queues)**
- Vulkan Documentation: **[QueueFamily](https://docs.vulkan.org/guide/latest/queues.html)**





