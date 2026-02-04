#ifndef MOD_SURFACE_HPP
#define MOD_SURFACE_HPP

#include <vulkan/vulkan.h>

struct instance_t;
struct window_t;

struct surface_t
{
	VkSurfaceKHR handle = VK_NULL_HANDLE;
};

void surface_create(surface_t* surface, const instance_t& instance, const window_t& window);

void surface_destroy(const surface_t& surface, const instance_t& instance);

#endif
