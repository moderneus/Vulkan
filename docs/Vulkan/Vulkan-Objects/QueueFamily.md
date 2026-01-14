# What is a QueueFamily?



# How to find the QueueFamily?

```cpp
struct QueueFamily
{
    std::optional<uint32_t> graphics;
    std::optional<uint32_t> present;
};
```

```cpp
void queue_family_find(QueueFamily* queue_family, const PhysicalDevice& phys_device, const Surface& surface) {
    log_info("Searching a Suitable Queue Families...");
    
    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(phys_device.handle, &queue_family_count, nullptr);
    
    std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(phys_device.handle, &queue_family_count, queue_families.data());

    for (uint32_t i = 0; i < queue_family_count ; ++i) {
        if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            queue_family->graphics = i;
        }
        VkBool32 present_support = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(phys_device.handle, i, surface.handle, &present_support);
        
        if(present_support) {
            queue_family->present = i;
        }
        if(queue_family_is_complete(*queue_family)) {
            break;
        }
    }
    if(!queue_family_is_complete(*queue_family)) {
        log_critical("Failed to Find any Suitable Queue Families!");
    }
    log_success("The Suitable Queue Families were Found!");
}
```

# Dependencies

# How to destroy?

# Links

- Vulkan Documentation: **[QueueFamily](https://docs.vulkan.org/guide/latest/queues.html)**
