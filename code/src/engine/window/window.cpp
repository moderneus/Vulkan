#include "engine/window/window.hpp"
#include "util/string.hpp"
#include "util/debug/log.hpp"

void window_create(window *win, const char *title, const uint32_t w, const uint32_t h) 
{
	log_info("Creating a Window...");

	win->handle = SDL_CreateWindow(title, w, h, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);

	if (!win->handle)
		log_critical("Failed to create the Window::" + cstr_to_str(SDL_GetError()));

	log_info("The Window was Created.");
}

void window_destroy(const window &win) 
{
	log_info("Destroying the Window...");

	if (win.handle == nullptr)
		log_critical("Cannot Destroy the Window::Window is not Created.");

	SDL_DestroyWindow(win.handle);

	log_info("The Window was Destroyed.");
}
