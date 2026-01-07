# What is an Instance?
The Instance is a Vulkan object that stores a context of your application. Unlike OpenGL you must create it explicitly. 
The context is set of conditions in which you run the program, such as API version, enabled extensions, enabled layers and a platform-specific details.
What is the extensions? Extensions are an additional functionality for Vulkan, each extension has a name like "*VK_EXT_debug_utils*". 
And what is the layers? Layers are implementations placed between the application and the driver, adding additional checks or modifying Vulkan behavior.

# How to create?

For all of the objects we'll create a relevant struct where we'll store the object handle. 

```cpp
struct Instance
{
    VkInstance handle = VK_NULL_HANDLE;
};
```

Almost all of the objects can be created by vkCreate*ObjectName()* function, for example: *vkCreateInstance()*, *vkCreateDevice()*, *vkCreateShaderModule()*, etc. 

```cpp
void instance_create(Instance* instance)
{
    VkApplicationInfo app_info = instance_create_app_info();
    VkDebugUtilsMessengerCreateInfoEXT debug_info = debug_msgr_create_info();
    std::vector<const char*> exts = instance_get_required_exts();
    VkInstanceCreateInfo instance_info = instance_create_info(&app_info, &debug_info, exts);
    
    if(vkCreateInstance(&instance_info, nullptr, &instance->handle) != VK_SUCCESS)
    {
        log_critical("Failed to Create an Instance!");
    }
}
```

But you can see that we have to create an info of this object. The info is just a struct with some fields (usually the settings) that we have to setup.
It's not difficult, but it might take the significant timew while you read the documentation and explore all of the values of this fields.
Since I'm writing it as note then I'll very briefly explain all of the fields and chosed value for it, I'll also skip any obviosly moments for brevity. 
If you want to know the details then you can find a link to the documentation at the very bottom.

So, let's take a look over the Instance info creation! Firstly we have to create an application info and then pass it to the Instance info. I did it in the relevant function:

```cpp
VkApplicationInfo instance_create_app_info()
{
    VkApplicationInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    create_info.pApplicationName = "Vulkan";
    create_info.applicationVersion = VK_MAKE_VERSION(1, 0, 1);
    create_info.pEngineName = "No Engine";
    create_info.engineVersion = VK_MAKE_VERSION(0, 1, 0);
    create_info.apiVersion = VK_API_VERSION_1_4;
    return create_info;
}
```

I think everything is obvious here, so we'll go further to the extensions enabling.

```cpp
std::vector<const char*> instance_get_required_exts()
{
    uint32_t exts_count = 0;
    const char* const* exts = SDL_Vulkan_GetInstanceExtensions(&exts_count);
    std::vector<const char*> exts_vec(exts, exts + exts_count);
    exts_vec.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    return exts_vec;
}
```

Since we're using a window system then we have to enable some extensions for presenting a rendered image to the screen, such as: *VK_KHR_surface*, *VK_KHR_win32_surface*. And also we need to enable the debug extension to receive a debug messages from the Validation Layers. I'll not explain now how to enable the Validation Layers and how to create a DebugMessenger, you can read it **[here](DebugMessenger.md)**. Well, to get the needed extensions for your platform from SDL we can use *SDL_Vulkan_GetInstanceExtensions(Uint32 \*count)* function. Next we're just copying the data from the array to the vector and adding the *VK_EXT_debug_utils* extension.
Now we have all to create the Instance info itself! 

```cpp
VkInstanceCreateInfo instance_create_info
(
    const VkApplicationInfo* app_info,
    const VkDebugUtilsMessengerCreateInfoEXT* debug_info,
    const std::vector<const char*>& exts
)
{
    VkInstanceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pNext = nullptr;
    create_info.pApplicationInfo = app_info;
    create_info.enabledExtensionCount = static_cast<uint32_t>(exts.size());
    create_info.ppEnabledExtensionNames = reinterpret_cast<const char* const*>(exts.data());
    
    if(check_validation_layers_support())
    {
        create_info.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        create_info.ppEnabledLayerNames = validationLayers.data();
        create_info.pNext = debug_info;
    }
    else
    {
        create_info.enabledLayerCount = 0;
        create_info.ppEnabledLayerNames = nullptr;
    }
    return create_info;
}
```

Everything here is pretty easy to understand except *sType* and *pNext* fields. Both of them are used to create a list of extension structures for base structure (in our case it's *VkInstanceCreateInfo*). We add pNext to the main structure, which is a pointer to an extension structure containing an sType field. When creating an object, the driver reads the main structure and applies the base features. Then it follows the pNext chain: for each structure, it checks the sType in a switch-like mechanism and, if supported, enables the corresponding flags and features. It continues down the linked list until pNext is NULL.

# Dependencies

Instance is located at the top of the hierarchy of objects, so it does not depend on anyone. All other objects depend on Instance in one way or another, since all extensions and layers that affect driver behavior are registered at the Instance level.

# How to destroy?

Very easy! 

```cpp
void instance_destroy(const Instance& instance)
{
    if(instance.handle == VK_NULL_HANDLE)
    {
        log_error("Cannot Destroy the Instance::Instance is not Created!");
    }
    vkDestroyInstance(instance.handle, nullptr);
}
```

# Links

Vulkan Specification: [Instance](https://registry.khronos.org/vulkan/specs/latest/html/vkspec.html#initialization-instances)
