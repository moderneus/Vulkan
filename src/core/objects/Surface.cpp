#include "core/objects/Surface.hpp"
#include "core/Core.hpp"
#include "util/debug/Logger.hpp"
#include "window/Window.hpp"

#include "SDL3/SDL_error.h"
#include "SDL3/SDL_vulkan.h"

void surface_create(Surface* surface) {
    log_info("Creating a Surface...");
    if(!SDL_Vulkan_CreateSurface(Window::Window::get(), Core::get()->getInstance(), nullptr, &surface->handle)) {
        log_critical("Failed to Create the Surface::", SDL_GetError()); 
    }
    log_success("The Surface was Created!");
}

void surface_destroy(const Surface& surface) {
    log_info("Destroying the Surface...");
    if(surface.handle == VK_NULL_HANDLE) {
        log_error("Cannot Destroy the Surface::Surface is not Created!");
    }
    SDL_Vulkan_DestroySurface(Core::get()->getInstance(), surface.handle, nullptr);
    log_success("The Surface was Destroyed!");
}
