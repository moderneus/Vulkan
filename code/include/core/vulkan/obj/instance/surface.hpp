#ifndef MOD_SURFACE_HPP
#define MOD_SURFACE_HPP

#include <vulkan/vulkan.h>

struct instance;
struct window;

struct surface {
	VkSurfaceKHR handle = VK_NULL_HANDLE;
};

void surface_create(surface *surf, const instance &inst, const window &win);

void surface_destroy(const surface &surf, const instance &inst);

#endif
