# What is a PhysicalDevice?

The PhysicalDevice is a Vulkan object that represents a specific graphics device available on the system. It is a purely informational object describing the device’s features, limits, and available queue families. It doesn't manage resources, allocate memory, or participate in command execution. However, the **[LogicalDevice](LogicalDevice.md)** will provide us with this capability.

# How to choose?

First of all let's create the wrapper of the PhysicalDevice. 

```cpp
struct PhysicalDevice
{
    VkPhysicalDevice handle = VK_NULL_HANDLE;
};
```

To choose the PhysicalDevice firstly we must enumrate them via *vkEnumeratePhysicalDevices()* function. Next we're initializing the vector with size equals *phys_device_count*. We call this function twice so that the phys_device_count variable does not have a garbage value and the vector is initialized with the correct size. Afterwards, we put our *candidates* into a multimap paired with their score to automatically sort them and avoid unnecessary duplication errors. Further we select the PhysicalDevice with the highest score.

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

But how to rate the PhysicalDevice? I did this in relevant function:

```cpp
uint32_t phys_device_rate(const VkPhysicalDevice& phys_device)
{
    VkPhysicalDeviceProperties phys_device_props;
    vkGetPhysicalDeviceProperties(phys_device, &phys_device_props);

    uint32_t score = 0;
    if(phys_device_props.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        score += 1000;
    
    score += phys_device_props.limits.maxImageDimension2D;
    return score;
}
```



# How to destroy?

# Dependencies

# Links

