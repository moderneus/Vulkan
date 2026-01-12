# What is a PhysicalDevice?

The PhysicalDevice is a Vulkan object that represents a specific graphics device available on the system. It is a purely informational object describing the device’s features, limits, and available queue families.

# How to choose?

First of all let's create the wrapper of the PhysicalDevice. 

```cpp
struct PhysicalDevice
{
    VkPhysicalDevice handle = VK_NULL_HANDLE;
};
```

To choose the PhysicalDevice firstly we must enumrate them via *vkEnumeratePhysicalDevices()* function.

```cpp
void phys_device_pick(PhysicalDevice* phys_device, const Instance& instance, const Surface& surface)
{
    uint32_t phys_device_count = 0;
    vkEnumeratePhysicalDevices(instance.handle, &phys_device_count, nullptr);
    
    if(phys_device_count == 0)
        log_critical("Failed to find GPU with Vulkan support!");

    std::vector<VkPhysicalDevice> phys_devices(phys_device_count);
    vkEnumeratePhysicalDevices(instance.handle, &phys_device_count, phys_devices.data());
    
    std::multimap<int, VkPhysicalDevice> candidates;
    for(const VkPhysicalDevice& phys_device : phys_devices)
    {
        uint32_t score = phys_device_rate(phys_device);
        candidates.insert(std::make_pair(score, phys_device));
    }

    if(candidates.rbegin()->first > 0)
        phys_device->handle = candidates.rbegin()->second;

    else if(!phys_device_is_suitable(phys_device->handle, surface.handle))
        log_critical("Failed to Find any Suitable GPU!");

    else
        log_critical("Failed to Find any Suitable GPU!");
}
```

# How to destroy?

# Dependencies

# Links
