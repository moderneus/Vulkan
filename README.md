# What's that?
**This is a self-study project ─ graphics Engine on C++ and the Vulkan API.**

# Architecture

````
Vulkan
├── headers
│   ├── core
│   │   ├── Core.hpp
│   │   ├── SDL.hpp
│   │   └── objects
│   │       ├── Instance.hpp
│   │       ├── LogicalDevice.hpp
│   │       ├── PhysicalDevice.hpp
│   │       └── QueueFamily.hpp    
│   ├── engine
│   │   └── Engine.hpp
│   ├── gfx
│   │   └── Renderer.hpp
│   ├── util
│   │   ├── EventManager.hpp
│   │   ├── Singleton.hpp
│   │   ├── String.hpp
│   │   └── debug
│   │       ├── Logger.hpp
│   │       └── ValidationLayers.hpp
│   └── window
│       └── Window.hpp
├── libs
│   ├── SDL
│   └── fmt
├── src
│   ├── Vulkan.cpp
│   ├── core
│   │   ├── Core.cpp
│   │   ├── SDL.cpp
│   │   └── objects
│   │       ├── Instance.hpp
│   │       ├── LogicalDevice.hpp
│   │       ├── PhysicalDevice.hpp
│   │       └── QueueFamily.hpp 
│   ├── engine
│   │   └── Engine.cpp
│   ├── gfx
│   │   └── Renderer.cpp
│   ├── util
│   │   ├── EventManager.cpp
│   │   ├── String.cpp
│   │   └── debug
│   │       ├── Logger.cpp
│   │       └── ValidationLayers.cpp
│   └── window
│       └── Window.cpp
├── CMakeLists.txt
├── LICENSE
└── README.md
````


