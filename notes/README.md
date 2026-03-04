# Preface

You shouldn't treat this as the Vulkan API documentation,  tutorial, or something like that. It's just my own understanding and my own view of Vulkan API that I’d like to share. I'm writing this as notes that I can use while I'm programming. If you have noticed that any of the explanations here is wrong then please open an issue and tell me about it so I can rewrite and fix it. By the way English is not my first language, so you might see many mistakes.

# Introduction

![Vulkan](images/vulkan.png) is the cross-platform graphics and compute API created by the Khronos Group. Vulkan was developed in 2016 to solve many problems of the previous APIs, 
such as OpenGL and Direct3D. Vulkan provides a very thorough setup process with explicit memory allocation. This allows both the driver and the programmer 
to avoid guessing any of those settings. Vulkan also allows the use of multi-threading by its architecture, which allows a programmer to create a high-performance 
graphics program. Personally I chose Vulkan because I'm interested in full control, performance and the modern API.

# Vulkan Objects

- **[Instance](Vulkan-Objects/Instance.md)**
- **[Surface](Vulkan-Objects/Surface.md)**
- **[PhysicalDevice](Vulkan-Objects/PhysicalDevice.md)**
- **[QueueFamily](Vulkan-Objects/QueueFamily.md)**
- **[Queue](Vulkan-Objects/Queue.md)**
- **[Device](Vulkan-Objects/Device.md)**
- **[Swapchain](Vulkan-Objects/Swapchain.md)**
- **[ImageView](Vulkan-Objects/ImageView.md)**
- **[RenderPass](Vulkan-Objects/Renderpass.md)**
- **[Framebuffer](Vulkan-Objects/Framebuffer.md)**
- **[PipelineLayout](Vulkan-Objects/PipelineLayout.md)**
- **[ShaderModule](Vulkan-Objects/ShaderModule.md)**
- **[Pipeline](Vulkan-Objects/Pipeline.md)**
- **[CommandPool](Vulkan-Objects/CommandPool.md)**
- **[CommandBuffer](Vulkan-Objects/CommandBuffer.md)**
- **[VertexBuffer](Vulkan-Objects/VertexBuffer.md)**
- **[Semaphore](Vulkan-Objects/Semaphore.md)**
- **[Fence](Vulkan-Objects/Fence.md)**
