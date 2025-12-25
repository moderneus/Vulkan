# Architecture
````
Vulkan
│ 
├── headers
│   ├── core
│   │   ├── SDL
│   │   │   └── SDL.hpp
│   │   └── vulkan
│   │       ├── Core.hpp
│   │       └── objects
│   │           ├── CommandBuffer.hpp
│   │           ├── CommandPool.hpp
│   │           ├── Fence.hpp
│   │           ├── Framebuffer.hpp
│   │           ├── ImageView.hpp
│   │           ├── Instance.hpp
│   │           ├── LogicalDevice.hpp
│   │           ├── PhysicalDevice.hpp
│   │           ├── Pipeline.hpp
│   │           ├── PipelineLayout.hpp
│   │           ├── Queue.hpp
│   │           ├── QueueFamily.hpp
│   │           ├── RenderPass.hpp
│   │           ├── Semaphore.hpp
│   │           ├── ShaderModule.hpp
│   │           ├── Surface.hpp
│   │           └── Swapchain.hpp
│   ├── engine
│   │   ├── Engine.hpp
│   │   ├── gfx
│   │   │   └── Renderer.hpp
│   │   └── window
│   │       └── Window.hpp
│   └── util
│       ├── Constants.hpp
│       ├── EventManager.hpp
│       ├── File.hpp
│       ├── String.hpp
│       └── debug
│           ├── Logger.hpp
│           └── ValidationLayers.hpp
├── libs
│   ├── SDL
│   └── fmt
│ 
├── shaders
│   ├── frag
│   │   ├── FragmentShader.frag
│   │   └── FragmentShader.spv
│   └── vert
│       ├── FragmentShader.spv
│       ├── VertexShader.spv
│       └── VertexShader.vert
│ 
├── src
│    ├── Vulkan.cpp
│    ├── core
│    │   ├── SDL
│    │   │   └── SDL.cpp
│    │   └── vulkan
│    │       ├── Core.cpp
│    │       └── objects
│    │           ├── CommandBuffer.cpp
│    │           ├── CommandPool.cpp
│    │           ├── Fence.cpp
│    │           ├── Framebuffer.cpp
│    │           ├── ImageView.cpp
│    │           ├── Instance.cpp
│    │           ├── LogicalDevice.cpp
│    │           ├── PhysicalDevice.cpp
│    │           ├── Pipeline.cpp
│    │           ├── PipelineLayout.cpp
│    │           ├── QueueFamily.cpp
│    │           ├── RenderPass.cpp
│    │           ├── Semaphore.cpp
│    │           ├── ShaderModule.cpp
│    │           ├── Surface.cpp
│    │           └── Swapchain.cpp
│    ├── engine
│    │   ├── Engine.cpp
│    │   ├── gfx
│    │   │   └── Renderer.cpp
│    │   └── window
│    │       └── Window.cpp
│    └── util
│        ├── EventManager.cpp
│        ├── File.cpp
│        ├── String.cpp
│        └── debug
│            ├── Logger.cpp
│            └── ValidationLayers.cpp
│ 
├── CMakeLists.txt
├── LICENSE
└── README.md
````