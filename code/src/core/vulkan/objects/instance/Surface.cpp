#include "core/vulkan/objects/instance/Surface.hpp"
#include "core/vulkan/objects/instance/Instance.hpp"
#include "engine/window/Window.hpp"
#include "util/debug/Logger.hpp"

#include "SDL3/SDL_error.h"
#include "SDL3/SDL_vulkan.h"

void surface_create(surface_t *surface, const instance_t &instance, const window_t &window) 
{
	log_info("Creating a Surface...");

	if (!SDL_Vulkan_CreateSurface(window.phandle, instance.handle, nullptr, &surface->handle)) {
		log_critical("Failed to Create the Surface::", SDL_GetError()); 
	}

	log_info("The Surface was Created.");
}

void surface_destroy(const surface_t &surface, const instance_t &instance) 
{
	log_info("Destroying the Surface...");

	if (surface.handle == VK_NULL_HANDLE) {
		log_error("Cannot Destroy the Surface::Surface is not Created.");
	}

	SDL_Vulkan_DestroySurface(instance.handle, surface.handle, nullptr);

	log_info("The Surface was Destroyed.");
}
