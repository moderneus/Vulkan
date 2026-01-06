# What is an Instance?
The Instance is a Vulkan object that stores a context of your application. Unlike OpenGL you must create it explicitly. 
The context is set of conditions in which you run the program, such as API version, enabled extensions, enabled layers and a platform-specific details.
What is the extensions? Extensions are an additional functionality for Vulkan, each extension has a name like "*VK_EXT_debug_utils*". 
And what is the layers? Layers are implementations placed between the application and the driver, adding additional checks or modifying Vulkan behavior.

# How to create?

In this file you can see the code of the Instance creation: [Instance.cpp](code/src/core/vulkan/objects/Instance.cpp)


# Dependencies

# How to destroy?

# Links
