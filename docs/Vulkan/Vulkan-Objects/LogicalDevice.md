# What is a LogicalDevice?

The LogicalDevice is a Vulkan object that represents the interface through which the application interacts with the GPU.
It manages memory allocations and resources.
The LogicalDevice is based on a PhysicalDevice and is created from it.
During creation, we must specify which queues, features, extensions, and layers will be used.

# How to create?

Let's write a simple wrapper of the LogicalDevice.

```cpp
struct LogicalDevice
{
    VkDevice handle = VK_NULL_HANDLE; // The main handle to the logical device. All Vulkan operations like creating buffers, images, or pipelines use this handle.
};
```

The PhysicalDevice represents the actual installed hardware; it's a purely informative Vulkan object. The LogicalDevice represents a specific PhysicalDevice and specifies how the application will use it. 
So before creating the LogicalDevice first, we must specify which queues, features, extensions, and layers will be used and bind them to the LogicalDevice info.

```cpp
void device_create(LogicalDevice* device, Queue* queue, const QueueFamily& queue_family, const PhysicalDevice& phys_device)
{
	// Vulkan allows multiple queues in a single queue family, each can have a priority.
    // Higher priority queues are preferred by the GPU scheduler when competing for execution.
    const float queue_priority = 1.0f; 
    
    // Prepare creation info for all queues we want to use on this device
    std::vector<VkDeviceQueueCreateInfo> queue_infos = device_create_queue_infos(queue_family, queue_priority);
    
    // Enable the GPU features we need (like geometry shaders)
    VkPhysicalDeviceFeatures phys_device_features = device_get_enabled_features(phys_device);
    
    // Fill the logical device creation info structure
    VkDeviceCreateInfo device_info = device_create_info(queue_infos, phys_device_features);
    
    // Actually create the logical device on the selected physical device
    if(vkCreateDevice(phys_device.handle, &device_info, nullptr, &device->handle) != VK_SUCCESS)
        log_critical("Failed to create the Logical Device!");
    
    // Retrieve the handles to the actual queues from the logical device
    // Queues are needed to submit commands to the GPU
    vkGetDeviceQueue(device->handle, queue_family.graphics.value(), 0, &queue->graphics); // Graphics queue
    vkGetDeviceQueue(device->handle, queue_family.present.value(), 0, &queue->present);   // Presentation queue
}
```

I started with specifying the queues. Here for every queue we're creating the queue info.
If the graphics and present queue families are equal we must create only one info. Otherwise we must create the present queue info separately.

```cpp
std::vector<VkDeviceQueueCreateInfo> device_create_queue_infos(const QueueFamily& queue_family, const float& queue_priority)
{
    std::vector<VkDeviceQueueCreateInfo> queue_infos;
    
    // If graphics and presentation queues belong to the same queue family,
    // we only need to create one queue info structure for both.
    if(queue_family.graphics == queue_family.present)
    {
        queue_infos.push_back(device_create_queue_info(queue_family.graphics.value(), queue_priority));
    } 
    else
    {
        // Otherwise, create separate queue info for each queue family
        queue_infos.push_back(device_create_queue_info(queue_family.graphics.value(), queue_priority));
        queue_infos.push_back(device_create_queue_info(queue_family.present.value(), queue_priority));
    }
    return queue_infos;
}
```

Here's how we create the queue info. Explanation of fields in comments.

```cpp
VkDeviceQueueCreateInfo device_create_queue_info(const uint32_t queue_family_idx, const float& queue_priority)
{
    VkDeviceQueueCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO; 
    create_info.queueFamilyIndex = queue_family_idx; // Index of the queue family this queue belongs to
    create_info.queueCount = 1; // Number of queues to create in this family
    create_info.pQueuePriorities = &queue_priority; // Pointer to an array of priorities for each queue in this family
    return create_info;
}
```

Now we can enable the features we want. Actually, I don't need the geometry shader feature, but I added it as an example.

```cpp
VkPhysicalDeviceFeatures device_get_enabled_features(const PhysicalDevice& phys_device)
{
	// Enable features we plan to use, for example geometry shaders
    // If a feature is not enabled here, the logical device won't allow creating resources that require it
    VkPhysicalDeviceFeatures features = {};
    features.geometryShader = phys_device_get_features(phys_device).geometryShader;
    return features;
}
```

For it I wrote an additional function in *PhysicalDevice.cpp*. I think everything is obvious here.

```cpp
VkPhysicalDeviceFeatures phys_device_get_features(const PhysicalDevice& phys_device)
{
    VkPhysicalDeviceFeatures phys_device_features = {};
    vkGetPhysicalDeviceFeatures(phys_device.handle, &phys_device_features); // Retrieve all features supported by the physical GPU

    if(phys_device_features.geometryShader != VK_TRUE) // Check that the GPU supports a feature we want to enable.
        log_critical("The found GPU doesn't have a Geometry Shader feature!");
    return phys_device_features;
}
```

All that's left is create the LogicalDevice info. Explanation of fields in comments.

```cpp
VkDeviceCreateInfo device_create_info(const std::vector<VkDeviceQueueCreateInfo>& queue_infos, const VkPhysicalDeviceFeatures& phys_device_features)
{
    VkDeviceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO; 
    create_info.queueCreateInfoCount = static_cast<uint32_t>(queue_infos.size()); 
    create_info.pQueueCreateInfos = queue_infos.data(); // Pass queue info to Vulkan so it knows which queues to create
    create_info.pEnabledFeatures = &phys_device_features; // Specify which GPU features we want to enable on this logical device
    create_info.enabledExtensionCount = static_cast<uint32_t>(phys_device_exts.size()); // Enabled extensions count 
    create_info.ppEnabledExtensionNames = phys_device_exts.data(); // Pass a pointer to an array of extensions to enable them
    return create_info;
}
```

# How to destroy?

```cpp
void device_destroy(const LogicalDevice& device) 
{
    if(device.handle == VK_NULL_HANDLE) 
        log_error("Cannot Destroy the Logical Device::Logical Device is not Created!");
    vkDestroyDevice(device.handle, nullptr); // Destroy the logical device and free all associated GPU resources
}
```

# Dependencies

The LogicalDevice depends on the Instance, since the PhysicalDevice, which serves as its foundation, depends on it. In particular, it relies on the enabled extensions, features, and layers. 
Many objects also depend on the LogicalDevice; these include Queues, CommandPools, Buffers, Images, ImageViews, DescriptorSets, Samplers, and Pipelines, as it manages the creation and lifetime of these resources.

# Links

- Vulkan Specification **[LogicalDevice](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#devsandqueues-devices)**
- Vulkan Documentation **[LogicalDevice](https://docs.vulkan.org/tutorial/latest/03_Drawing_a_triangle/00_Setup/04_Logical_device_and_queues.html)**
