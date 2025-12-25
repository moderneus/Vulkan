#include "core/vulkan/objects/Surface.hpp"
#include "core/vulkan/objects/Instance.hpp"
#include "engine/window/Window.hpp"
#include "util/debug/Logger.hpp"

#include "SDL3/SDL_error.h"
#include "SDL3/SDL_vulkan.h"

void surface_create(Surface* surface, const Instance& instance, const Window& window) {
    log_info("Creating a Surface...");
    if(!SDL_Vulkan_CreateSurface(window.pwindow, instance.handle, nullptr, &surface->handle)) {
        log_critical("Failed to Create the Surface::", SDL_GetError()); 
    }
    log_success("The Surface was Created!");
}

void surface_destroy(const Surface& surface, const Instance& instance) {
    log_info("Destroying the Surface...");
    if(surface.handle == VK_NULL_HANDLE) {
        log_error("Cannot Destroy the Surface::Surface is not Created!");
    }
    SDL_Vulkan_DestroySurface(instance.handle, surface.handle, nullptr);
    log_success("The Surface was Destroyed!");
}
