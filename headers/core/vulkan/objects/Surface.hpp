#pragma once

#include "core/vulkan/objects/Instance.hpp"
#include "engine/window/Window.hpp"

#include <vulkan/vulkan.h>

struct Surface {
    VkSurfaceKHR handle = VK_NULL_HANDLE;
};

void surface_create(Surface* surface, const Instance& instance, const Window& window);

void surface_destroy(const Surface& surface, const Instance& instance);
