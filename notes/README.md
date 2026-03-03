# Preface

You shouldn't treat this as the Vulkan API documentation,  tutorial, or something like that. It's just my own understanding and my own view of Vulkan API that I’d like to share. I'm writing this as notes that I can use while I'm programming. If you have noticed that any of the explanations here is wrong then please open an issue and tell me about it so I can rewrite and fix it. By the way English is not my first language, so you might see many mistakes.

# Introduction

![Vulkan](images/vulkan.png) is the cross-platform graphics and compute API created by the Khronos Group. Vulkan was developed in 2016 to solve many problems of the previous APIs, 
such as OpenGL and Direct3D. Vulkan provides a very thorough setup process with explicit memory allocation. This allows both the driver and the programmer 
to avoid guessing any of those settings. Vulkan also allows the use of multi-threading by its architecture, which allows a programmer to create a high-performance 
graphics program. Personally I chose Vulkan because I'm interested in full control, performance and the modern API.

# Vulkan Objects

***<pre>
<a href="Vulkan-Objects/Instance.md">Instance</a>
├── <a href="Vulkan-Objects/PhysicalDevice.md">PhysicalDevice</a>
│   ├── <a href="Vulkan-Objects/LogicalDevice.md">Device</a>
│   │   ├── <a href="Vulkan-Objects/CommandPool.md">CommandPool</a>
│   │   │   └── <a href="Vulkan-Objects/CommandBuffer.md">CommandBuffer</a>
│   │   ├── <a href="Vulkan-Objects/Fence.md">Fence</a>
│   │   ├── <a href="Vulkan-Objects/Framebuffer.md">Framebuffer</a>
│   │   ├── <a href="Vulkan-Objects/ImageView.md">ImageView</a>
│   │   ├── <a href="Vulkan-Objects/Pipeline.md">Pipeline</a>
│   │   ├── <a href="Vulkan-Objects/PipelineLayout.md">PipelineLayout</a>
│   │   ├── <a href="Vulkan-Objects/Queue.md">Queue</a>
│   │   ├── <a href="Vulkan-Objects/Renderpass.md">RenderPass</a>
│   │   ├── <a href="Vulkan-Objects/Semaphore.md">Semaphore</a>
│   │   ├── <a href="Vulkan-Objects/ShaderModule.md">ShaderModule</a>
│   │   ├── <a href="Vulkan-Objects/Swapchain.md">Swapchain</a>
│   │   │   └── <a href="Vulkan-Objects/Image.md">Image</a>
│   │   └── <a href="Vulkan-Objects/VertexBuffer.md">VertexBuffer</a>
│   └── <a href="Vulkan-Objects/QueueFamily.md">QueueFamily</a>
└── <a href="Vulkan-Objects/Surface.md">Surface</a>
</pre>***
