#pragma once

#include <vulkan/vulkan.h>

struct Surface {
    VkSurfaceKHR handle = VK_NULL_HANDLE;
};

void surface_create();

void surface_destroy();
