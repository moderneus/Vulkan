# What is a PhysicalDevice?

The PhysicalDevice is a Vulkan object that represents a specific graphics device available on the system. It is a purely informational object describing the device’s features, limits, and available queue families. It doesn't manage resources, allocate memory, or participate in command execution. 

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

But how to rate the PhysicalDevice? Here we evaluate the PhysicalDevice score based on our program's preferences. Thus, we fill our multimap in a loop and since it is always sorted, we only have to choose the first PhysicalDevice. 

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

The device is selected, but if we want to display images on the screen, we need to enable the *VK_KHR_swapchain* extension. We will store all the necessary extensions in the const char vector.

```cpp
const std::vector<const char*> phys_device_exts = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
```

The *phys_device_is_suitable()* function returns true if the selected physical device supports the required extensions and if the swapchain supports the required formats and present modes. 

```cpp
bool phys_device_is_suitable(const VkPhysicalDevice& phys_device, const VkSurfaceKHR& surface)
{
    return phys_device_check_ext_support(phys_device) && swapchain_is_adequate(phys_device, surface);
}
```

Here we collect all available extensions, and place our enabled ones in a set for performance. Now, if our enabled extension is present in the available ones, we erase it. If all enabled extensions are available, the vector will remain empty. If the vector is empty, the extensions are supported.

```cpp
bool phys_device_check_ext_support(const VkPhysicalDevice& phys_device)
{
    uint32_t ext_count;
    vkEnumerateDeviceExtensionProperties(phys_device, nullptr, &ext_count, nullptr);
    
    std::vector<VkExtensionProperties> exts(ext_count);
    vkEnumerateDeviceExtensionProperties(phys_device, nullptr, &ext_count, exts.data());
    
    std::set<std::string> required_exts(phys_device_exts.begin(), phys_device_exts.end());

    for(const auto& ext : exts) 
        required_exts.erase(ext.extensionName);
    
    return required_exts.empty();
}
```

Congratulations, we have selected a PhysicalDevice with the parameters we need and can now make it the basis for a **[LogicalDevice](LogicalDevice.md)**.

# How to destroy?

You don't need to manually destroy the PhysicalDevice, it is destroyed automatically along with the Instance.

# Dependencies

The PhysicalDevice is created after the VkInstance and depends only on it, as the Vulkan instance determines which physical devices are available on the system.
It has no mutable state and does not depend on any LogicalDevice or resources.

The creation of a LogicalDevice directly depends on the PhysicalDevice, since it defines the available queues, features, limits, and extensions.
All Vulkan resources and operations ultimately rely on the selected PhysicalDevice through the corresponding LogicalDevice.


# Links

Vulkan Specification: **[PhysicalDevice](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#devsandqueues-physical-device-enumeration)**

Vulkan Documentation: **[PhysicalDevice](https://docs.vulkan.org/refpages/latest/refpages/source/VkPhysicalDevice.html)**




