# Architecture

<pre>
code
├── <a href="./CMakeLists.txt">CMakeLists.txt</a>
│
├── include
│   ├── core
│   │   ├── sdl
│   │   │   └── <a href="./include/core/sdl/sdl_ctx.hpp">sdl_ctx.hpp</a>
│   │   └── vulkan
│   │       ├── <a href="./include/core/vulkan/core.hpp">core.hpp</a>
│   │       └── obj
│   │           ├── buffer
│   │           │   ├── <a href="./include/core/vulkan/obj/buffer/vertex.hpp">vertex.hpp</a>
│   │           │   └── <a href="./include/core/vulkan/obj/buffer/vertex_buffer.hpp">vertex_buffer.hpp</a>
│   │           ├── command
│   │           │   ├── <a href="./include/core/vulkan/obj/command/command_buffer.hpp">command_buffer.hpp</a>
│   │           │   └── <a href="./include/core/vulkan/obj/command/command_pool.hpp">command_pool.hpp</a>
│   │           ├── debug
│   │           │   └── <a href="./include/core/vulkan/obj/debug/messenger.hpp">messenger.hpp</a>
│   │           ├── device
│   │           │   ├── <a href="./include/core/vulkan/obj/device/device.hpp">device.hpp</a>
│   │           │   ├── <a href="./include/core/vulkan/obj/device/physical_device.hpp">physical_device.hpp</a>
│   │           │   ├── <a href="./include/core/vulkan/obj/device/queue.hpp">queue.hpp</a>
│   │           │   └── <a href="./include/core/vulkan/obj/device/queue_indices.hpp">queue_indices.hpp</a>
│   │           ├── instance
│   │           │   ├── <a href="./include/core/vulkan/obj/instance/instance.hpp">instance.hpp</a>
│   │           │   └── <a href="./include/core/vulkan/obj/instance/surface.hpp">surface.hpp</a>
│   │           ├── pipeline
│   │           │   ├── <a href="./include/core/vulkan/obj/pipeline/layout.hpp">layout.hpp</a>
│   │           │   ├── <a href="./include/core/vulkan/obj/pipeline/pipeline.hpp">pipeline.hpp</a>
│   │           │   └── <a href="./include/core/vulkan/obj/pipeline/shader.hpp">shader.hpp</a>
│   │           ├── renderpass
│   │           │   └── <a href="./include/core/vulkan/obj/renderpass/render_pass.hpp">render_pass.hpp</a>
│   │           ├── swapchain
│   │           │   ├── <a href="./include/core/vulkan/obj/swapchain/framebuffer.hpp">framebuffer.hpp</a>
│   │           │   ├── <a href="./include/core/vulkan/obj/swapchain/image_view.hpp">image_view.hpp</a>
│   │           │   └── <a href="./include/core/vulkan/obj/swapchain/swapchain.hpp">swapchain.hpp</a>
│   │           └── sync
│   │               ├── <a href="./include/core/vulkan/obj/sync/fence.hpp">fence.hpp</a>
│   │               └── <a href="./include/core/vulkan/obj/sync/semaphore.hpp">semaphore.hpp</a>
│   │
│   ├── engine
│   │   ├── <a href="./include/engine/engine.hpp">engine.hpp</a>
│   │   ├── event
│   │   │   └── <a href="./include/engine/event/event_manager.hpp">event_manager.hpp</a>
│   │   ├── gfx
│   │   │   └── <a href="./include/engine/gfx/renderer.hpp">renderer.hpp</a>
│   │   └── window
│   │       └── <a href="./include/engine/window/window.hpp">window.hpp</a>
│   │
│   └── util
│       ├── <a href="./include/util/constants.hpp">constants.hpp</a>
│       ├── debug
│       │   ├── <a href="./include/util/debug/log.hpp">log.hpp</a>
│       │   └── <a href="./include/util/debug/val_layers.hpp">val_layers.hpp</a>
│       ├── <a href="./include/util/file.hpp">file.hpp</a>
│       └── <a href="./include/util/string.hpp">string.hpp</a>
│
├── libs
│   ├── SDL
│   ├── fmt
│   └── glm
│
├── shaders
│   ├── frag
│   │   └── <a href="./shaders/frag/triangle.frag">triangle.frag</a>
│   └── vert
│       └── <a href="./shaders/vert/triangle.vert">triangle.vert</a>
│
└── src
    ├── core
    │   ├── sdl
    │   │   └── <a href="./src/core/SDL/sdl_ctx.cpp">sdl_ctx.cpp</a>
    │   └── vulkan
    │       ├── <a href="./src/core/vulkan/core.cpp">core.cpp</a>
    │       └── obj
    │           ├── buffer
    │           │   ├── <a href="./src/core/vulkan/obj/buffer/vertex.cpp">vertex.cpp</a>
    │           │   └── <a href="./src/core/vulkan/obj/buffer/vertex_buffer.cpp">vertex_buffer.cpp</a>
    │           ├── command
    │           │   ├── <a href="./src/core/vulkan/obj/command/command_buffer.cpp">command_buffer.cpp</a>
    │           │   └── <a href="./src/core/vulkan/obj/command/command_pool.cpp">command_pool.cpp</a>
    │           ├── debug
    │           │   └── <a href="./src/core/vulkan/obj/debug/messenger.cpp">messenger.cpp</a>
    │           ├── device
    │           │   ├── <a href="./src/core/vulkan/obj/device/device.cpp">device.cpp</a>
    │           │   ├── <a href="./src/core/vulkan/obj/device/physical_device.cpp">physical_device.cpp</a>
    │           │   ├── <a href="./src/core/vulkan/obj/device/queue.cpp">queue.cpp</a>
    │           │   └── <a href="./src/core/vulkan/obj/device/queue_indices.cpp">queue_indices.cpp</a>
    │           ├── instance
    │           │   ├── <a href="./src/core/vulkan/obj/instance/instance.cpp">instance.cpp</a>
    │           │   └── <a href="./src/core/vulkan/obj/instance/surface.cpp">surface.cpp</a>
    │           ├── pipeline
    │           │   ├── <a href="./src/core/vulkan/obj/pipeline/layout.cpp">layout.cpp</a>
    │           │   ├── <a href="./src/core/vulkan/obj/pipeline/pipeline.cpp">pipeline.cpp</a>
    │           │   └── <a href="./src/core/vulkan/obj/pipeline/shader.cpp">shader.cpp</a>
    │           ├── renderpass
    │           │   └── <a href="./src/core/vulkan/obj/renderpass/render_pass.cpp">render_pass.cpp</a>
    │           ├── swapchain
    │           │   ├── <a href="./src/core/vulkan/obj/swapchain/framebuffer.cpp">framebuffer.cpp</a>
    │           │   ├── <a href="./src/core/vulkan/obj/swapchain/image_view.cpp">image_view.cpp</a>
    │           │   └── <a href="./src/core/vulkan/obj/swapchain/swapchain.cpp">swapchain.cpp</a>
    │           └── sync
    │               ├── <a href="./src/core/vulkan/obj/sync/fence.cpp">fence.cpp</a>
    │               └── <a href="./src/core/vulkan/obj/sync/semaphore.cpp">semaphore.cpp</a>
    │
    ├── engine
    │   ├── <a href="./src/engine/engine.cpp">engine.cpp</a>
    │   ├── event
    │   │   └── <a href="./src/engine/event/event_manager.cpp">event_manager.cpp</a>
    │   ├── gfx
    │   │   └── <a href="./src/engine/gfx/renderer.cpp">renderer.cpp</a>
    │   └── window
    │       └── <a href="./src/engine/window/window.cpp">window.cpp</a>
    │
    ├── util
    │   ├── debug
    │   │   ├── <a href="./src/util/debug/log.cpp">log.cpp</a>
    │   │   └── <a href="./src/util/debug/val_layers.cpp">val_layers.cpp</a>
    │   ├── <a href="./src/util/file.cpp">file.cpp</a>
    │   └── <a href="./src/util/string.cpp">string.cpp</a>
    │
    └── <a href="./src/vulkan.cpp">vulkan.cpp</a>
</pre>
