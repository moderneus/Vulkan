# Architecture
```
code
├── CMakeLists.txt
├── include
│   ├── core
│   │   ├── sdl
│   │   │   └── sdl_ctx.hpp
│   │   └── vulkan
│   │       ├── core.hpp
│   │       └── obj
│   │           ├── buffer
│   │           │   ├── vertex.hpp
│   │           │   └── vertex_buffer.hpp
│   │           ├── command
│   │           │   ├── command_buffer.hpp
│   │           │   └── command_pool.hpp
│   │           ├── debug
│   │           │   └── messenger.hpp
│   │           ├── device
│   │           │   ├── device.hpp
│   │           │   ├── physical_device.hpp
│   │           │   ├── queue.hpp
│   │           │   └── queue_indices.hpp
│   │           ├── instance
│   │           │   ├── instance.hpp
│   │           │   └── surface.hpp
│   │           ├── pipeline
│   │           │   ├── layout.hpp
│   │           │   ├── pipeline.hpp
│   │           │   └── shader.hpp
│   │           ├── renderpass
│   │           │   └── render_pass.hpp
│   │           ├── swapchain
│   │           │   ├── framebuffer.hpp
│   │           │   ├── image_view.hpp
│   │           │   └── swapchain.hpp
│   │           └── sync
│   │               ├── fence.hpp
│   │               └── semaphore.hpp
│   ├── engine
│   │   ├── engine.hpp
│   │   ├── event
│   │   │   └── event_manager.hpp
│   │   ├── gfx
│   │   │   └── renderer.hpp
│   │   └── window
│   │       └── window.hpp
│   └── util
│       ├── constants.hpp
│       ├── debug
│       │   ├── log.hpp
│       │   └── val_layers.hpp
│       ├── file.hpp
│       └── string.hpp
├── libs
│   ├── SDL
│   ├── fmt
│   └── glm
├── shaders
│   ├── frag
│   │   └── triangle.frag
│   └── vert
│       └── triangle.vert
└── src
    ├── core
    │   ├── sdl
    │   │   └── sdl_ctx.cpp
    │   └── vulkan
    │       ├── core.cpp
    │       └── obj
    │           ├── buffer
    │           │   ├── vertex.cpp
    │           │   └── vertex_buffer.cpp
    │           ├── command
    │           │   ├── command_buffer.cpp
    │           │   └── command_pool.cpp
    │           ├── debug
    │           │   └── messenger.cpp
    │           ├── device
    │           │   ├── device.cpp
    │           │   ├── physical_device.cpp
    │           │   ├── queue.cpp
    │           │   └── queue_indices.cpp
    │           ├── instance
    │           │   ├── instance.cpp
    │           │   └── surface.cpp
    │           ├── pipeline
    │           │   ├── layout.cpp
    │           │   ├── pipeline.cpp
    │           │   └── shader.cpp
    │           ├── renderpass
    │           │   └── render_pass.cpp
    │           ├── swapchain
    │           │   ├── framebuffer.cpp
    │           │   ├── image_view.cpp
    │           │   └── swapchain.cpp
    │           └── sync
    │               ├── fence.cpp
    │               └── semaphore.cpp
    ├── engine
    │   ├── engine.cpp
    │   ├── event
    │   │   └── event_manager.cpp
    │   ├── gfx
    │   │   └── renderer.cpp
    │   └── window
    │       └── window.cpp
    ├── util
    │   ├── debug
    │   │   ├── log.cpp
    │   │   └── val_layers.cpp
    │   ├── file.cpp
    │   └── string.cpp
    └── vulkan.cpp
```
