#include "core/vulkan/obj/instance/surface.hpp"
#include "core/vulkan/obj/instance/instance.hpp"
#include "engine/window/window.hpp"
#include "util/debug/log.hpp"

#include "SDL3/SDL_error.h"
#include "SDL3/SDL_vulkan.h"

void surface_create(surface *surf, const instance &inst, const window &win) 
{
	log_info("Creating a Surface...");

	if (!SDL_Vulkan_CreateSurface(win.handle, inst.handle, nullptr, &surf->handle))
		log_critical("Failed to Create the Surface::", SDL_GetError()); 

	log_info("The Surface was Created.");
}

void surface_destroy(const surface &surf, const instance &inst) 
{
	log_info("Destroying the Surface...");

	if (surf.handle == VK_NULL_HANDLE)
		log_error("Cannot Destroy the Surface::Surface is not Created.");

	SDL_Vulkan_DestroySurface(inst.handle, surf.handle, nullptr);

	log_info("The Surface was Destroyed.");
}
