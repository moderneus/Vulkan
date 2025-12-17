# Architecture

````
Vulkan
├── CMakeLists.txt
├── LICENSE
├── README.md
├── docs
│   └── Fundamentals
│       └── Vulkan Objects
│           ├── README.md
│           └── topics
│               ├── Buffer.md
│               ├── CommandBuffer.md
│               ├── Image.md
│               ├── Instance.md
│               ├── Logicalevice.md
│               ├── PhysicalDevice.md
│               ├── Pipeline.md
│               ├── Queue.md
│               ├── RenderPass.md
│               ├── Sampler.md
│               ├── Surface.md
│               └── Swapchain.md
├── headers
│   ├── core
│   │   ├── SDL
│   │   │   └── SDL.hpp
│   │   └── vulkan
│   │       ├── Core.hpp
│   │       └── objects
│   │           ├── ImageView.hpp
│   │           ├── Instance.hpp
│   │           ├── LogicalDevice.hpp
│   │           ├── PhysicalDevice.hpp
│   │           ├── Pipeline.hpp
│   │           ├── PipelineLayout.hpp
│   │           ├── QueueFamily.hpp
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
│       ├── debug
│       │   ├── Logger.hpp
│       │   └── ValidationLayers.hpp
│       ├── EventManager.hpp
│       ├── File.hpp
│       └── String.hpp
├── libs
│   ├── SDL
│   └── fmt
├── shaders
│   ├── frag
│   │   ├── FragmentShader.frag
│   │   └── FragmentShader.spv
│   └── vert
│       ├── VertexShader.spv
│       └── VertexShader.vert
└── src
    ├── core
    │   ├── SDL
    │   │   └── SDL.cpp
    │   └── vulkan
    │       ├── Core.cpp
    │       └── objects
    │           ├── ImageView.cpp
    │           ├── Instance.cpp
    │           ├── LogicalDevice.cpp
    │           ├── PhysicalDevice.cpp
    │           ├── Pipeline.cpp
    │           ├── PipelineLayout.cpp
    │           ├── QueueFamily.cpp
    │           ├── ShaderModule.cpp
    │           ├── Surface.cpp
    │           └── Swapchain.cpp
    ├── engine
    │   ├── Engine.cpp
    │   ├── gfx
    │   │   └── Renderer.cpp
    │   └── window
    │       └── Window.cpp
    ├── util
    │   ├── debug
    │   │   ├── Logger.cpp
    │   │   └── ValidationLayers.cpp
    │   ├── EventManager.cpp
    │   ├── File.cpp
    │   └── String.cpp
    └── Vulkan.cpp
````
