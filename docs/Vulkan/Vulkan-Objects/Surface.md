# What is a Surface?

The Surface is a Vulkan object that stores the context of the connected window system. In this case, the context is usually just a set of window handles.
The Surface context allows the driver to determine the format, size, quantity, queues, and mode the application can output frames to a given window on a given device. 
Note that Surface is part of the core WSI extension set because Vulkan is for rendering and not for presenting. If you want to present something to the screen, you must enable the necessary extensions. 

But what is format, size, quantity, queue and mode? 
- Format – The pixel format and color space the presented images use.
- Size – The dimensions of the images that can be presented.
- Quantity – How many images can exist in the swapchain simultaneously.
- Queue – Which queue families are allowed to present images to the surface.
- Mode – How image presentation is synchronized with the display system.

You can read about the possible values ​​in the documentation. 

# How to create? 

We are not going to create platform-specific surfaces manually. SDL provides us with a function to create Surface for our platform *SDL_Vulkan_CreateSurface()*.

```cpp
void surface_create(Surface* surface, const Instance& instance, const Window& window)
{
    if(!SDL_Vulkan_CreateSurface(window.pwindow, instance.handle, nullptr, &surface->handle))
    {
        log_critical("Failed to Create the Surface::", SDL_GetError()); 
    }
}
```

# How to destroy?

Here we can also use the SDL function *SDL_Vulkan_DestroySurface()*.

```cpp
void surface_destroy(const Surface& surface, const Instance& instance)
{
    if(surface.handle == VK_NULL_HANDLE)
    {
        log_error("Cannot Destroy the Surface::Surface is not Created!");
    }
    SDL_Vulkan_DestroySurface(instance.handle, surface.handle, nullptr);
}
```

# Dependencies

## What Surface depends on:

- VkInstance: A Surface is an instance-level object. It is created via instance-level WSI functions and exists within the lifetime of the VkInstance.

- Window system objects: A Surface is associated with a native window provided by the operating system (e.g. HWND, wl_surface, xcb_window_t). Vulkan does not own or manage the window; it only references it.

- Enabled WSI extensions: At least, VK_KHR_surface must be enabled, along with an appropriate platform-specific surface extension. Without these extensions, a Surface cannot be created.

- No direct dependency on a device: A Surface can be created without selecting a physical or logical device. Its compatibility with devices is evaluated later.

## What depends on Surface:

- Physical device surface queries: A Surface is required to query presentation capabilities of a physical device:

    - Supported formats.

    - Supported image extents.

    - Supported present modes.

    - Queue family presentation support.

- Queue family selection: Surface support determines which queue families can perform presentation. This affects whether a single graphics queue can be used or a separate present queue is required.

- Swapchain: A Swapchain is created for a specific Surface and cannot be shared between Surfaces. The lifetime and validity of the swapchain depend on the Surface.

- Swapchain images and presentation resources: Images, image views, framebuffers, and synchronization objects derived from a swapchain are indirectly dependent on the Surface.

- Presentation lifecycle behavior: Surface constraints affect resize handling, presentation errors (VK_ERROR_OUT_OF_DATE_KHR, VK_SUBOPTIMAL_KHR), and the need to recreate the swapchain.

# Links

Vulkan Documentation: **[Surface](https://docs.vulkan.org/tutorial/latest/03_Drawing_a_triangle/01_Presentation/00_Window_surface.html)**


