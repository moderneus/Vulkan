# What is a QueueFamily?

A queue family is a hardware-defined set of queues with identical command execution capabilities. It can contain queues optimized for specific commands: graphics, compute, transfer, and presentation. A queue is a concrete hardware execution stream. Commands are submitted to a queue and executed on the GPU in sequence. Different queues may execute in parallel.

# How to find the QueueFamily?

```cpp
struct QueueFamily
{
    std::optional<uint32_t> graphics;
    std::optional<uint32_t> present;
};
```

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

```cpp
bool queue_family_is_complete(const QueueFamily& queue_family)
{
    return queue_family.graphics.has_value() && queue_family.present.has_value();
}
```

# Dependencies

# How to destroy?

# Links

- Vulkan Documentation: **[QueueFamily](https://docs.vulkan.org/guide/latest/queues.html)**

