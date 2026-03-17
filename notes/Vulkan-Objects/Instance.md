# What is an Instance?

The Instance is a Vulkan object that stores a context of your application. The context is set of conditions in which you run the program, such as API version, enabled extensions, 
enabled layers and a platform-specific details. Extensions are an additional functionality for Vulkan, each extension has a name like "*VK_EXT_debug_utils*". Layers are 
implementations placed between the application and the driver, adding additional checks or modifying Vulkan behavior.

When creating the Instance everything is pretty easy to understand except the *sType* and *pNext* fields in «info-structures». Both of them are used to create a list of extension 
structures for base structure. We add pNext to the main structure, which is a pointer to an extension structure containing an sType field. When creating an object, the driver reads 
the main structure and enables the base features. Then it follows the pNext chain: for each structure, it checks the sType in a switch-like mechanism and enables the 
corresponding flags and features. It continues down the linked list until pNext is NULL.

# Dependencies

Instance is located at the top of the hierarchy of objects, so it does not depend on anything. All other objects depend on Instance in one way or another, since all extensions and 
layers that affect driver behavior are registered at the Instance level.

# Links

- Vulkan Specification: **[Instance](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#initialization-instances)**
- Vulkan Documentation: **[Instance](https://docs.vulkan.org/tutorial/latest/03_Drawing_a_triangle/00_Setup/01_Instance.html)**

