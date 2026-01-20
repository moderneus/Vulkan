# What is a LogicalDevice?

The LogicalDevice is a Vulkan object that represents the interface through which the application interacts with the GPU.
It manages memory allocations and resources.
The LogicalDevice is based on a PhysicalDevice and is created from it.
During creation, we must specify which queues, features, extensions, and layers are used.

# How to create?

```cpp
struct LogicalDevice
{
    VkDevice handle = VK_NULL_HANDLE;
}
```

```cpp
void device_create(LogicalDevice* device, Queue* queue, const QueueFamily& queue_family, const PhysicalDevice& phys_device) 
{
    VkPhysicalDeviceFeatures features = {};
    VkDeviceQueueCreateInfo queue_info = device_create_queue_info(queue_family);
    VkDeviceCreateInfo device_info = device_create_info(phys_device, queue_info, &features);

    if(vkCreateDevice(phys_device.handle, &device_info, nullptr, &device->handle) != VK_SUCCESS) 
        log_critical("Failed to Create the Logical Device!");
    
    vkGetDeviceQueue(device->handle, queue_family.graphics.value(), 0, &queue->graphics);
    vkGetDeviceQueue(device->handle, queue_family.present.value(), 0, &queue->present);
}
```

```cpp
VkDeviceQueueCreateInfo device_create_queue_info(const QueueFamily& queue_family) 
{
    VkDeviceQueueCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    create_info.queueFamilyIndex = queue_family.graphics.value();
    create_info.queueCount = 1;
    const float queuePriority = 1.0f;
    create_info.pQueuePriorities = &queuePriority;
    return create_info;
}
```

```cpp
VkDeviceCreateInfo device_create_info(const PhysicalDevice& phys_device, const VkDeviceQueueCreateInfo& queue_info, VkPhysicalDeviceFeatures* phys_device_features) 
{
    VkDeviceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    create_info.pQueueCreateInfos = &queue_info;
    create_info.queueCreateInfoCount = 1;
    phys_device_features->geometryShader = phys_device_get_features(phys_device).geometryShader;
    create_info.pEnabledFeatures = phys_device_features;
    create_info.enabledExtensionCount = static_cast<uint32_t>(phys_device_exts.size());
    create_info.ppEnabledExtensionNames = phys_device_exts.data();
    create_info.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    create_info.ppEnabledLayerNames = validationLayers.data();
    return create_info;
}
```

# How to destroy?

```cpp
void device_destroy(const LogicalDevice& device) 
{
    if(device.handle == VK_NULL_HANDLE) 
        log_error("Cannot Destroy the Logical Device::Logical Device is not Created!");
    vkDestroyDevice(device.handle, nullptr);
}
```

# Dependencies

# Links

- Vulkan Specification **[LogicalDevice](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#devsandqueues-devices)**
- Vulkan Documentation **[LogicalDevice](https://docs.vulkan.org/tutorial/latest/03_Drawing_a_triangle/00_Setup/04_Logical_device_and_queues.html)**