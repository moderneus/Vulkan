# What is a QueueFamily?

A queue family is a hardware-defined set of queues with identical command execution capabilities. It can contain queues optimized for specific commands: graphics, compute, transfer, and presentation. A queue is a concrete hardware execution stream. Commands are submitted to a queue and executed on the GPU in sequence. Different queues may execute in parallel.

# How to find the QueueFamily?

Before we search for the queues we need: graphics and present. Each queue family has its own index: 0, 1, 2, etc. We'll create a structure to conveniently store them. 
We made them optional so that we could easily check whether the indices of these families were found.

```cpp
struct QueueFamily
{
    std::optional<uint32_t> graphics;
    std::optional<uint32_t> present;
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
    vkGetPhysicalDeviceQueueFamilyProperties(phys_device.handle, &queue_family_count, nullptr);
    
    std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(phys_device.handle, &queue_family_count, queue_families.data());

    for (uint32_t i = 0; i < queue_family_count; ++i)
    {
        if(queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) 
            queue_family->graphics = i;
        
        VkBool32 present_support = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(phys_device.handle, i, surface.handle, &present_support);
        
        if(present_support) 
            queue_family->present = i;
        
        if(queue_family_is_complete(*queue_family)) 
            break;    
    }
    if(!queue_family_is_complete(*queue_family)) 
        log_critical("Failed to Find any Suitable Queue Families!");
}
```

Here we simply return true if we found the indices of the required families.

```cpp
bool queue_family_is_complete(const QueueFamily& queue_family)
{
    return queue_family.graphics.has_value() && queue_family.present.has_value();
}
```

# Dependencies

# How to destroy?

They don't require clearing, and you don't create queue families or queues anywhere. It's a hardware-based part of Vulkan.

# Links

- Vulkan Documentation: **[QueueFamily](https://docs.vulkan.org/guide/latest/queues.html)**


