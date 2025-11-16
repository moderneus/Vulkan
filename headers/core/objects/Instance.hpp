#pragma once

#include <vulkan/vulkan.h>

class Instance
{
private: 
    VkInstance instance;

    VkApplicationInfo createAppInfo();
    VkInstanceCreateInfo createInstanceInfo(VkApplicationInfo* appInfo);

public: 
    void create();
    void destroy();
    
    VkInstance& get();
};
