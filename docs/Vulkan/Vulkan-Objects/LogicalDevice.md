# What is a LogicalDevice?

The LogicalDevice is a Vulkan object that represents the interface through which the application interacts with the GPU.
It manages memory allocations and resources.
The LogicalDevice is based on a PhysicalDevice and is created from it.
During creation, we must specify which queues, features, extensions, and layers are used.

# How to create?

Let's write a simple wrapper of the LogicalDevice.

```cpp
struct LogicalDevice
{
    VkDevice handle = VK_NULL_HANDLE;
}
```

Since LogicalDevice is an interface of the PhysicalDevice we must specify 

```cpp
VkPhysicalDeviceFeatures device_get_enabled_features(const PhysicalDevice& phys_device)
{
    VkPhysicalDeviceFeatures features = {};
    features.geometryShader = phys_device_get_features(phys_device).geometryShader;
    return features;
}
```

```cpp
std::vector<VkDeviceQueueCreateInfo> device_create_queue_infos(const QueueFamily& queue_family, const float& queue_priority)
{
	std::vector<VkDeviceQueueCreateInfo> queue_infos;
	if(queue_family.graphics == queue_family.present)
    {
		queue_infos.push_back(device_create_queue_info(queue_family.graphics.value(), queue_priority));
	} 
	else
    {
		queue_infos.push_back(device_create_queue_info(queue_family.graphics.value(), queue_priority));
		queue_infos.push_back(device_create_queue_info(queue_family.present.value(), queue_priority));
	}
	return queue_infos;
}
```

```cpp
VkDeviceQueueCreateInfo device_create_queue_info(const uint32_t queue_family_idx, const float& queue_priority)
{
    VkDeviceQueueCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    create_info.queueFamilyIndex = queue_family_idx;
    create_info.queueCount = 1;
    create_info.pQueuePriorities = &queue_priority;
    return create_info;
}
```

```cpp
VkDeviceCreateInfo device_create_info(const std::vector<VkDeviceQueueCreateInfo>& queue_infos, const VkPhysicalDeviceFeatures& phys_device_features)
{
    VkDeviceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    create_info.queueCreateInfoCount = static_cast<uint32_t>(queue_infos.size());
    create_info.pQueueCreateInfos = queue_infos.data();
    create_info.pEnabledFeatures = &phys_device_features;
    create_info.enabledExtensionCount = static_cast<uint32_t>(phys_device_exts.size());
    create_info.ppEnabledExtensionNames = phys_device_exts.data();
    return create_info;
}
```

```cpp
void device_create(LogicalDevice* device, Queue* queue, const QueueFamily& queue_family, const PhysicalDevice& phys_device)
{
    const float queue_priority = 1.0f;
	std::vector<VkDeviceQueueCreateInfo> queue_infos = device_create_queue_infos(queue_family, queue_priority);
    VkPhysicalDeviceFeatures phys_device_features = device_get_enabled_features(phys_device);
    VkDeviceCreateInfo device_info = device_create_info(queue_infos, phys_device_features);
    
    if(vkCreateDevice(phys_device.handle, &device_info, nullptr, &device->handle) != VK_SUCCESS)
        log_critical("Failed to Create the Logical Device!");
    
    vkGetDeviceQueue(device->handle, queue_family.graphics.value(), 0, &queue->graphics);
    vkGetDeviceQueue(device->handle, queue_family.present.value(), 0, &queue->present);
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
