#pragma once

#include <vulkan/vulkan.h>

struct Instance;
struct Window;

struct Surface {
    VkSurfaceKHR handle = VK_NULL_HANDLE;
};

void surface_create(Surface* surface, const Instance& instance, const Window& window);

void surface_destroy(const Surface& surface, const Instance& instance);
