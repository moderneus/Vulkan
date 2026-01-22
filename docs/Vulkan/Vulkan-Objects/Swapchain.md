# What is a Swapchain?

The Swapchain is a Vulkan object that represents a set of images with a fixed format and size, organized as a queue that manages rendering and presentation of frames through a selected presentation mode. 
The swapchain itself decides which image is used for rendering, which image is queued for presentation, and which image is currently being displayed.
During rendering, the application only needs to acquire an available image and submit the rendering commands to the graphics queue. 
The swapchain is part of WSI: Vulkan handles rendering, not presentation.

# How to create?

```cpp
struct SwapchainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> present_modes;
};
```



```cpp
struct Swapchain
{
    VkSwapchainKHR handle = VK_NULL_HANDLE;
    VkExtent2D extent = {};
    VkFormat format = VK_FORMAT_UNDEFINED;
    VkColorSpaceKHR color_space = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    std::vector<VkFramebuffer> frame_buffers;
    std::vector<VkImageView> views; 
    std::vector<VkImage> imgs;
};
```



```cpp
SwapchainSupportDetails swapchain_query_support_details(const VkPhysicalDevice& phys_device, const VkSurfaceKHR& surface)
{
    SwapchainSupportDetails details;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(phys_device, surface, &details.capabilities);
    
    uint32_t formats_count;
    vkGetPhysicalDeviceSurfaceFormatsKHR(phys_device, surface, &formats_count, nullptr);
    if(formats_count != 0)
    {
        details.formats.resize(formats_count);
        vkGetPhysicalDeviceSurfaceFormatsKHR(phys_device, surface, &formats_count, details.formats.data());
    }
    uint32_t present_mode_count;
    vkGetPhysicalDeviceSurfacePresentModesKHR(phys_device, surface, &present_mode_count, nullptr);
    if(present_mode_count != 0)
    {
        details.present_modes.resize(present_mode_count);
        vkGetPhysicalDeviceSurfacePresentModesKHR(phys_device, surface, &present_mode_count, details.present_modes.data());
    }
    return details;
}
```

```cpp
bool swapchain_is_adequate(const VkPhysicalDevice& phys_device, const VkSurfaceKHR& surface)
{
    SwapchainSupportDetails details = swapchain_query_support_details(phys_device, surface);
    return !details.formats.empty() && !details.present_modes.empty();
}
```



```cpp
VkSurfaceFormatKHR swapchain_choose_format(const std::vector<VkSurfaceFormatKHR>& formats)
{
    if(formats.size() == 1 && formats[0].format == VK_FORMAT_UNDEFINED)
        return {VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
    
    for(const auto& format : formats)
    {
        if(format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
            return format;
    }
    return formats[0];
}
```



```cpp
VkPresentModeKHR swapchain_choose_present_mode(const std::vector<VkPresentModeKHR>& present_modes)
{
    for(const auto& present_mode : present_modes)
    {
        if(present_mode == VK_PRESENT_MODE_MAILBOX_KHR)
            return present_mode;
    }
    return VK_PRESENT_MODE_FIFO_KHR;
}
```

```cpp
VkExtent2D swapchain_choose_extent(const Window& window, const VkSurfaceCapabilitiesKHR& capabilities)
{
    if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
    {
        return capabilities.currentExtent;
    }
    else
    {
        int width, height;
        SDL_GetWindowSizeInPixels(window.pwindow, &width, &height); 
        VkExtent2D extent
        {
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height)
        };
        extent.width = std::clamp(extent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        extent.height = std::clamp(extent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
        return extent;
    }
}
```



```cpp
VkSwapchainCreateInfoKHR swapchain_create_info
(
    const QueueFamily& queue_family,
    const Surface& surface,
    const VkSurfaceFormatKHR& format, 
    const VkPresentModeKHR& present_mode, 
    const VkExtent2D& extent, 
    const VkSurfaceCapabilitiesKHR& capabilities, 
    uint32_t img_count
)
{
    VkSwapchainCreateInfoKHR create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    create_info.surface = surface.handle;
    create_info.minImageCount = img_count;
    create_info.imageColorSpace = format.colorSpace;
    create_info.imageFormat = format.format;
    create_info.imageExtent = extent;
    create_info.imageArrayLayers = 1;
    create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    
    uint32_t queue_family_indices[] = {queue_family.graphics.value(), queue_family.present.value()};
    
    if(queue_family.graphics != queue_family.present)
    {
        create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        create_info.queueFamilyIndexCount = 2;
        create_info.pQueueFamilyIndices = queue_family_indices;
    }
    else
    {
        create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        create_info.queueFamilyIndexCount = 0;
        create_info.pQueueFamilyIndices = nullptr;
    }
    create_info.preTransform = capabilities.currentTransform;
    create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    create_info.presentMode = present_mode;
    create_info.clipped = VK_TRUE;
    create_info.oldSwapchain = VK_NULL_HANDLE;
    return create_info;
}
```



```cpp
void swapchain_create
(
    Swapchain* swapchain,
    const LogicalDevice& device,
    const PhysicalDevice& phys_device,
    const QueueFamily& queue_family,
    const Window& window,
    const Surface& surface
)
{
    SwapchainSupportDetails details = swapchain_query_support_details(phys_device.handle, surface.handle);
    VkSurfaceFormatKHR format = swapchain_choose_format(details.formats);
    VkPresentModeKHR present_mode = swapchain_choose_present_mode(details.present_modes);
    VkExtent2D extent = swapchain_choose_extent(window, details.capabilities);
    swapchain->format = format.format;
    swapchain->extent = extent;
    
    uint32_t img_count = details.capabilities.minImageCount + 1;
    if(details.capabilities.maxImageCount > 0 && img_count > details.capabilities.maxImageCount) 
        img_count = details.capabilities.maxImageCount;
    
    VkSwapchainCreateInfoKHR swapchain_info = swapchain_create_info(queue_family, surface, format, present_mode, extent, details.capabilities, img_count);

    if(vkCreateSwapchainKHR(device.handle, &swapchain_info, nullptr, &swapchain->handle) != VK_SUCCESS) 
        log_critical("Failed to Create the Swapchain!");
}
```

# How to destroy?

```cpp
void swapchain_destroy(const Swapchain& swapchain, const LogicalDevice& device)
{
    if(swapchain.handle == VK_NULL_HANDLE) 
        log_error("Cannot Destroy the Swapchain::Swapchain is not Created!");
    vkDestroySwapchainKHR(device.handle, swapchain.handle, nullptr);
}
```

# Dependencies

The Swapchain depends on the Surface, the PhysicalDevice capabilities (supported formats, present modes, image count), and queues that support presentation. 
Based on the Swapchain, its Images, ImageViews, and corresponding Framebuffers are created. 
The Swapchain’s format and extent define the RenderPasses and all attachments used for on-screen rendering. 
When the Surface changes or becomes incompatible, the Swapchain and all dependent Vulkan objects must be recreated.

# Links

- Vulkan Documentation **[Swapchain](https://docs.vulkan.org/tutorial/latest/03_Drawing_a_triangle/01_Presentation/01_Swap_chain.html)**
