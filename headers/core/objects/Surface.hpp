#pragma once

#include "core/objects/Instance.hpp"
#include "window/Window.hpp"

#include <vulkan/vulkan.h>

struct Surface {
    VkSurfaceKHR handle = VK_NULL_HANDLE;
};

void surface_create(const Instance& instance, const Window& window, Surface* surface);

void surface_destroy(const Instance& instance, const Surface& surface);
