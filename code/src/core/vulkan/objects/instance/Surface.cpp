#include "core/vulkan/objects/instance/Surface.hpp"
#include "core/vulkan/objects/instance/Instance.hpp"
#include "engine/window/Window.hpp"
#include "util/debug/Logger.hpp"

#include "SDL3/SDL_error.h"
#include "SDL3/SDL_vulkan.h"

void surf_create(surface_t *surf, const instance_t &inst, const window_t &win) 
{
	log_info("Creating a Surface...");

	if (!SDL_Vulkan_CreateSurface(win.handle, inst.handle, nullptr, &surf->handle)) {
		log_critical("Failed to Create the Surface::", SDL_GetError()); 
	}

	log_info("The Surface was Created.");
}

void surf_destroy(const surface_t &surf, const instance_t &inst) 
{
	log_info("Destroying the Surface...");

	if (surf.handle == VK_NULL_HANDLE) {
		log_error("Cannot Destroy the Surface::Surface is not Created.");
	}

	SDL_Vulkan_DestroySurface(inst.handle, surf.handle, nullptr);

	log_info("The Surface was Destroyed.");
}
