# What is a Surface?

The Surface is a Vulkan object of a certain type that stores the context of the connected window system. In this case the context ussualy is just the set of window handles.
The Surface context allows the driver to determine in what format, what size, in what quantity, in what queues and in what mode the application can output frames to a given window on a given device. 
Note that Surface is part of the core WSI extension set because Vulkan is for rendering and not for presenting. If you want to present something to the screen then you must enable the relevant extensions. 

Here are the possible types for different platforms:
- *VK_KHR_win32_surface* — Windows
- *VK_KHR_xcb_surface* — Linux X11
- *VK_KHR_wayland_surface* — Linux Wayland
- *VK_EXT_metal_surface* — MacOS

Of course Vulkan supports a way more various platforms, you can read it in documentation. 

# How to create? 

# How to destroy?

# Dependencies

# Links
