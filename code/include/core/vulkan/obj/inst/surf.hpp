#ifndef MOD_SURFACE_HPP
#define MOD_SURFACE_HPP

#include <vulkan/vulkan.h>

struct instance_t;
struct window_t;

struct surface_t
{
	VkSurfaceKHR handle = VK_NULL_HANDLE;
};

void surf_create(surface_t *surf, const instance_t &inst, const window_t &win);

void surf_destroy(const surface_t &surf, const instance_t &inst);

#endif
