#include "core/objects/Surface.hpp"
#include "core/Core.hpp"
#include "util/debug/Logger.hpp"
#include "window/Window.hpp"

#include "SDL3/SDL_error.h"
#include "SDL3/SDL_vulkan.h"

void Engine::Core::Surface::create()
{
    Utils::Logger::get()->info("Creating a Surface...");

    if(!SDL_Vulkan_CreateSurface(Window::Window::get(), Core::get()->getInstance(), nullptr, &surface))
        Utils::Logger::get()->critical("Failed to Create the Surface::", SDL_GetError()); 

    Utils::Logger::get()->success("The Surface was Created!");
}

void Engine::Core::Surface::destroy()
{
    Utils::Logger::get()->info("Destroying the Surface...");

    if(surface == VK_NULL_HANDLE)
        Utils::Logger::get()->error("Cannot Destroy the Surface::Surface is not Created!");

    SDL_Vulkan_DestroySurface(Core::get()->getInstance(), surface, nullptr);

    Utils::Logger::get()->success("The Surface was Destroyed!");
}

VkSurfaceKHR Engine::Core::Surface::get() const
{    
    return surface;
}
