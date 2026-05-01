# Architecture.

<pre>
code
│
├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/CMakeLists.txt">CMakeLists.txt</a>
│
├── assets
│   ├── models
│   │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/assets/models/viking_room.obj">viking_room.obj</a>
│   └── textures
│       └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/assets/textures/viking_room.png">viking_room.png</a>
│
├── include
│   ├── core
│   │   ├── sdl
│   │   │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/sdl/sdl_ctx.hpp">sdl_ctx.hpp</a>
│   │   └── vulkan
│   │       ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/core.hpp">core.hpp</a>
│   │       └── obj
│   │           ├── buffer
│   │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/buffer/buffer.hpp">buffer.hpp</a>
│   │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/buffer/index_buffer.hpp">index_buffer.hpp</a>
│   │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/buffer/uniform_buffer.hpp">uniform_buffer.hpp</a>
│   │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/buffer/vertex.hpp">vertex.hpp</a>
│   │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/buffer/vertex_buffer.hpp">vertex_buffer.hpp</a>
│   │           ├── command
│   │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/command/command_buffer.hpp">command_buffer.hpp</a>
│   │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/command/command_pool.hpp">command_pool.hpp</a>
│   │           ├── debug
│   │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/debug/messenger.hpp">messenger.hpp</a>
│   │           ├── descriptor
│   │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/descriptor/descriptor_pool.hpp">descriptor_pool.hpp</a>
│   │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/descriptor/descriptor_set.hpp">descriptor_set.hpp</a>
│   │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/descriptor/descriptor_set_layout.hpp">descriptor_set_layout.hpp</a>
│   │           ├── device
│   │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/device/device.hpp">device.hpp</a>
│   │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/device/physical_device.hpp">physical_device.hpp</a>
│   │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/device/queue.hpp">queue.hpp</a>
│   │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/device/queue_indices.hpp">queue_indices.hpp</a>
│   │           ├── image/
│   │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/image/color_image.hpp">color_image.hpp</a>
│   │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/image/depth_image.hpp">depth_image.hpp</a>
│   │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/image/image.hpp">image.hpp</a>
│   │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/image/image_view.hpp">image_view.hpp</a>
│   │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/image/sampler.hpp">sampler.hpp</a>
│   │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/image/texture.hpp">texture.hpp</a>
│   │           ├── instance
│   │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/instance/instance.hpp">instance.hpp</a>
│   │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/instance/surface.hpp">surface.hpp</a>
│   │           ├── model
│   │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/model/model.hpp">model.hpp</a>
│   │           ├── pipeline
│   │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/pipeline/pipeline.hpp">pipeline.hpp</a>
│   │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/pipeline/pipeline_layout.hpp">pipeline_layout.hpp</a>
│   │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/pipeline/shader.hpp">shader.hpp</a>
│   │           ├── renderpass
│   │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/renderpass/render_pass.hpp">render_pass.hpp</a>
│   │           ├── swapchain
│   │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/swapchain/framebuffer.hpp">framebuffer.hpp</a>
│   │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/swapchain/swapchain.hpp">swapchain.hpp</a>
│   │           └── sync
│   │               ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/sync/fence.hpp">fence.hpp</a>
│   │               ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/sync/memory_barrier.hpp">memory_barrier.hpp</a>
│   │               └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/core/vulkan/obj/sync/semaphore.hpp">semaphore.hpp</a>
│   │
│   ├── engine
│   │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/engine/engine.hpp">engine.hpp</a>
│   │   ├── event
│   │   │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/engine/event/event_manager.hpp">event_manager.hpp</a>
│   │   ├── gfx
│   │   │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/engine/gfx/renderer.hpp">renderer.hpp</a>
│   │   └── window
│   │       └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/engine/window/window.hpp">window.hpp</a>
│   │
│   └── util
│       ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/util/constants.hpp">constants.hpp</a>
│       ├── debug
│       │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/util/debug/log.hpp">log.hpp</a>
│       │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/util/debug/val_layers.hpp">val_layers.hpp</a>
│       ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/util/file.hpp">file.hpp</a>
│       └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/include/util/string.hpp">string.hpp</a>
│
├── shaders
│   ├── frag
│   │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/shaders/frag/viking_room.frag">viking_room.frag</a>
│   └── vert
│       └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/shaders/vert/viking_room.vert">viking_room.vert</a>
│
└── src
    ├── core
    │   ├── sdl
    │   │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/SDL/sdl_ctx.cpp">sdl_ctx.cpp</a>
    │   └── vulkan
    │       ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/core.cpp">core.cpp</a>
    │       └── obj
    │           ├── buffer
    │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/buffer/buffer.cpp">buffer.cpp</a>
    │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/buffer/index_buffer.cpp">index_buffer.cpp</a>
    │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/buffer/uniform_buffer.cpp">uniform_buffer.cpp</a>
    │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/buffer/vertex.cpp">vertex.cpp</a>
    │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/buffer/vertex_buffer.cpp">vertex_buffer.cpp</a>
    │           ├── command
    │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/command/command_buffer.cpp">command_buffer.cpp</a>
    │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/command/command_pool.cpp">command_pool.cpp</a>
    │           ├── debug
    │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/debug/messenger.cpp">messenger.cpp</a>
    │           ├── descriptor
    │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/descriptor/descriptor_pool.cpp">descriptor_pool.cpp</a>
    │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/descriptor/descriptor_set.cpp">descriptor_set.cpp</a>
    │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/descriptor/descriptor_set_layout.cpp">descriptor_set_layout.cpp</a>
    │           ├── device
    │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/device/device.cpp">device.cpp</a>
    │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/device/physical_device.cpp">physical_device.cpp</a>
    │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/device/queue.cpp">queue.cpp</a>
    │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/device/queue_indices.cpp">queue_indices.cpp</a>
    │           ├── image
    │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/image/color_image.cpp">color_image.cpp</a>
    │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/image/depth_image.cpp">depth_image.cpp</a>
    │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/image/image.cpp">image.cpp</a>
    │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/image/image_view.cpp">image_view.cpp</a>
    │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/image/sampler.cpp">sampler.cpp</a>
    │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/image/texture.cpp">texture.cpp</a>
    │           ├── instance
    │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/instance/instance.cpp">instance.cpp</a>
    │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/instance/surface.cpp">surface.cpp</a>
    │           ├── model
    │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/model/model.cpp">model.cpp</a>
    │           ├── pipeline
    │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/pipeline/pipeline.cpp">pipeline.cpp</a>
    │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/pipeline/pipeline_layout.cpp">pipeline_layout.cpp</a>
    │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/pipeline/shader.cpp">shader.cpp</a>
    │           ├── renderpass
    │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/renderpass/render_pass.cpp">render_pass.cpp</a>
    │           ├── swapchain
    │           │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/swapchain/framebuffer.cpp">framebuffer.cpp</a>
    │           │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/swapchain/swapchain.cpp">swapchain.cpp</a>
    │           └── sync
    │               ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/sync/fence.cpp">fence.cpp</a>
    │               ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/sync/memory_barrier.cpp">memory_barrier.cpp</a>
    │               └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/core/vulkan/obj/sync/semaphore.cpp">semaphore.cpp</a>
    ├── engine
    │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/engine/engine.cpp">engine.cpp</a>
    │   ├── event
    │   │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/engine/event/event_manager.cpp">event_manager.cpp</a>
    │   ├── gfx
    │   │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/engine/gfx/renderer.cpp">renderer.cpp</a>
    │   └── window
    │       └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/engine/window/window.cpp">window.cpp</a>
    │
    ├── util
    │   ├── debug
    │   │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/util/debug/log.cpp">log.cpp</a>
    │   │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/util/debug/val_layers.cpp">val_layers.cpp</a>
    │   ├── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/util/file.cpp">file.cpp</a>
    │   └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/util/string.cpp">string.cpp</a>
    │
    └── <a href="https://github.com/moderneus/Vulkan/blob/master/code/src/vulkan.cpp">vulkan.cpp</a>
</pre>
