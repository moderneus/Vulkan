#include "engine/window/Window.hpp"
#include "util/String.hpp"
#include "util/debug/Logger.hpp"

void win_create(window_t *win, const char *title, const uint32_t w, const uint32_t h) 
{
	log_info("Creating a Window...");

	win->handle = SDL_CreateWindow(title, w, h, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);

	if (!win->handle) {
		log_critical("Failed to create the Window::" + cstr_to_str(SDL_GetError()));
	}

	log_info("The Window was Created.");
}

void win_destroy(const window_t &win) 
{
	log_info("Destroying the Window...");

	if (win.handle == nullptr) {
		log_critical("Cannot Destroy the Window::Window is not Created.");
	}

	SDL_DestroyWindow(win.handle);

	log_info("The Window was Destroyed.");
}
