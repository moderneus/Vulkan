# Architecture
````
code
│
├── headers
│   ├── core
│   │   ├── SDL
│   │   │   └── SDL.hpp
│   │   └── vulkan
│   │       ├── Core.hpp
│   │       └── objects
│   │           ├── commands
│   │           │   ├── CommandBuffer.hpp
│   │           │   └── CommandPool.hpp
│   │           ├── debug
│   │           │   └── DebugMessenger.hpp
│   │           ├── device
│   │           │   ├── LogicalDevice.hpp
│   │           │   ├── PhysicalDevice.hpp
│   │           │   ├── QueueFamily.hpp
│   │           │   └── Queue.hpp
│   │           ├── instance
│   │           │   ├── Instance.hpp
│   │           │   └── Surface.hpp
│   │           ├── pipeline
│   │           │   ├── Pipeline.hpp
│   │           │   ├── PipelineLayout.hpp
│   │           │   └── ShaderModule.hpp
│   │           ├── renderpass
│   │           │   └── RenderPass.hpp
│   │           ├── swapchain
│   │           │   ├── Framebuffer.hpp
│   │           │   ├── ImageView.hpp
│   │           │   └── Swapchain.hpp
│   │           └── sync
│   │               ├── Fence.hpp
│   │               └── Semaphore.hpp
│   │
│   ├── engine
│   │   ├── Engine.hpp
│   │   ├── gfx
│   │   │   └── Renderer.hpp
│   │   └── window
│   │       └── Window.hpp
│   │
│   └── util
│       ├── Constants.hpp
│       ├── debug
│       │   ├── Logger.hpp
│       │   └── ValidationLayers.hpp
│       ├── EventManager.hpp
│       ├── File.hpp
│       └── String.hpp
│
├── libs
│   ├── SDL
│   └── fmt
│
├── shaders
│   ├── frag
│   │   └── FragmentShader.frag
│   └── vert
│       └── VertexShader.vert
│
├── src
│   ├── core
│   │   ├── SDL
│   │   │   └── SDL.cpp
│   │   └── vulkan
│   │       ├── Core.cpp
│   │       └── objects
│   │           ├── commands
│   │           │   ├── CommandBuffer.cpp
│   │           │   └── CommandPool.cpp
│   │           ├── debug
│   │           │   └── DebugMessenger.cpp
│   │           ├── device
│   │           │   ├── LogicalDevice.cpp
│   │           │   ├── PhysicalDevice.cpp
│   │           │   └── QueueFamily.cpp
│   │           ├── instance
│   │           │   ├── Instance.cpp
│   │           │   └── Surface.cpp
│   │           ├── pipeline
│   │           │   ├── Pipeline.cpp
│   │           │   ├── PipelineLayout.cpp
│   │           │   └── ShaderModule.cpp
│   │           ├── renderpass
│   │           │   └── RenderPass.cpp
│   │           ├── swapchain
│   │           │   ├── Framebuffer.cpp
│   │           │   ├── ImageView.cpp
│   │           │   └── Swapchain.cpp
│   │           └── sync
│   │               ├── Fence.cpp
│   │               └── Semaphore.cpp
│   │
│   ├── engine
│   │   ├── Engine.cpp
│   │   ├── gfx
│   │   │   └── Renderer.cpp
│   │   └── window
│   │       └── Window.cpp
│   │   
│   ├── util
│   │   ├── debug
│   │   │   ├── Logger.cpp
│   │   │   └── ValidationLayers.cpp
│   │   ├── EventManager.cpp
│   │   ├── File.cpp
│   │   └── String.cpp
│   └── Vulkan.cpp
│
├── README.md 
└── CMakeLists.txt
````
