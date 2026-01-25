#include "engine/window/Window.hpp"
#include "util/String.hpp"
#include "util/debug/Logger.hpp"

void window_create(window_t* window, const char* title, const uint32_t width, const uint32_t height) 
{
	log_info("Creating a Window...");

	window->pwindow = SDL_CreateWindow(title, width, height, SDL_WINDOW_VULKAN);

	if (!window->pwindow) {
		log_critical("Failed to create the Window::" + cstr_to_str(SDL_GetError()));
	}

	log_info("The Window was Created.");
}

void window_destroy(const window_t& window) 
{
	log_info("Destroying the Window...");

	if (window.pwindow == nullptr) {
		log_critical("Cannot Destroy the Window::Window is not Created.");
	}

	SDL_DestroyWindow(window.pwindow);

	log_info("The Window was Destroyed.");
}
