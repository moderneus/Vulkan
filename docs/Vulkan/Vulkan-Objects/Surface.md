# What is a Surface?

The Surface is a Vulkan object of a certain type that stores the context of the connected window system. In this case the context ussualy is just the set of window handles.
The Surface context allows the driver to determine in what format, what size, in what quantity, in what queues and in what mode the application can output frames to a given window on a given device. 
Note that Surface is part of the core WSI extension set because Vulkan is for rendering and not for presenting. If you want to present something to the screen then you must enable the necessary extensions. 

But what is format, size, quantity, queue and mode? 
- Format – What pixel format and color space the presented images use.
- Size – The dimensions of the images that can be presented.
- Quantity – How many images can exist in the swapchain at once.
- Queue – Which queue families are allowed to present images to the surface.
- Mode – How image presentation is synchronized with the display system.

You can read about possible values ​​in the documentation. 

# How to create? 

We're not going to create the Surface for the specific platforms manually. SDL provides us with a function to create Surface for our platform *SDL_Vulkan_CreateSurface()*.

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

Here we also can use the SDL function *SDL_Vulkan_DestroySurface()*.

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

# Links

