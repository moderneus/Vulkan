# Architecture

```
code
├── CMakeLists.txt
│
├── assets
│   └── textures
│       └── texture.png
│
├── include
│   ├── core
│   │   ├── sdl
│   │   │   └── sdl_ctx.hpp
│   │   └── vulkan
│   │       ├── core.hpp
│   │       └── obj
│   │           ├── buffer
│   │           │   ├── buffer.hpp
│   │           │   ├── index_buffer.hpp
│   │           │   ├── uniform_buffer.hpp
│   │           │   ├── vertex_buffer.hpp
│   │           │   └── vertex.hpp
│   │           ├── command
│   │           │   ├── command_buffer.hpp
│   │           │   └── command_pool.hpp
│   │           ├── debug
│   │           │   └── messenger.hpp
│   │           ├── descriptor
│   │           │   ├── descriptor_pool.hpp
│   │           │   ├── descriptor_set.hpp
│   │           │   └── descriptor_set_layout.hpp
│   │           ├── device
│   │           │   ├── device.hpp
│   │           │   ├── physical_device.hpp
│   │           │   ├── queue.hpp
│   │           │   └── queue_indices.hpp
│   │           ├── image
│   │           │   ├── image.hpp
│   │           │   ├── image_view.hpp
│   │           │   ├── sampler.hpp
│   │           │   └── texture.hpp
│   │           ├── instance
│   │           │   ├── instance.hpp
│   │           │   └── surface.hpp
│   │           ├── pipeline
│   │           │   ├── pipeline.hpp
│   │           │   ├── pipeline_layout.hpp
│   │           │   └── shader.hpp
│   │           ├── renderpass
│   │           │   └── render_pass.hpp
│   │           ├── swapchain
│   │           │   ├── framebuffer.hpp
│   │           │   └── swapchain.hpp
│   │           └── sync
│   │               ├── fence.hpp
│   │               ├── memory_barrier.hpp
│   │               └── semaphore.hpp
│   │
│   ├── engine
│   │   ├── engine.hpp
│   │   ├── event
│   │   │   └── event_manager.hpp
│   │   ├── gfx
│   │   │   └── renderer.hpp
│   │   └── window
│   │       └── window.hpp
│   │
│   └── util
│       ├── constants.hpp
│       ├── debug
│       │   ├── log.hpp
│       │   └── val_layers.hpp
│       ├── file.hpp
│       └── string.hpp
│
├── shaders
│   ├── frag
│   │   └── square.frag
│   └── vert
│       └── square.vert
└── src
    ├── core
    │   ├── SDL
    │   │   └── sdl_ctx.cpp
    │   └── vulkan
    │       ├── core.cpp
    │       └── obj
    │           ├── buffer
    │           │   ├── buffer.cpp
    │           │   ├── index_buffer.cpp
    │           │   ├── uniform_buffer.cpp
    │           │   ├── vertex_buffer.cpp
    │           │   └── vertex.cpp
    │           ├── command
    │           │   ├── command_buffer.cpp
    │           │   └── command_pool.cpp
    │           ├── debug
    │           │   └── messenger.cpp
    │           ├── descriptor
    │           │   ├── descriptor_pool.cpp
    │           │   ├── descriptor_set.cpp
    │           │   └── descriptor_set_layout.cpp
    │           ├── device
    │           │   ├── device.cpp
    │           │   ├── physical_device.cpp
    │           │   ├── queue.cpp
    │           │   └── queue_indices.cpp
    │           ├── image
    │           │   ├── image.cpp
    │           │   ├── image_view.cpp
    │           │   ├── sampler.cpp
    │           │   └── texture.cpp
    │           ├── instance
    │           │   ├── instance.cpp
    │           │   └── surface.cpp
    │           ├── pipeline
    │           │   ├── pipeline.cpp
    │           │   ├── pipeline_layout.cpp
    │           │   └── shader.cpp
    │           ├── renderpass
    │           │   └── render_pass.cpp
    │           ├── swapchain
    │           │   ├── framebuffer.cpp
    │           │   └── swapchain.cpp
    │           └── sync
    │               ├── fence.cpp
    │               ├── memory_barrier.cpp
    │               └── semaphore.cpp
    ├── engine
    │   ├── engine.cpp
    │   ├── event
    │   │   └── event_manager.cpp
    │   ├── gfx
    │   │   └── renderer.cpp
    │   └── window
    │       └── window.cpp
    │
    ├── util
    │   ├── debug
    │   │   ├── log.cpp
    │   │   └── val_layers.cpp
    │   ├── file.cpp
    │   └── string.cpp
    └── vulkan.cpp
```
