#include "core/sdl/sdl_ctx.hpp"
#include "util/string.hpp"
#include "util/debug/log.hpp"

#include "SDL3/SDL_init.h"

bool is_init = false;

void sdl_ctx_init() 
{
	log_info("Initializing the SDL...");

	if (is_init)
		log_error("SDL is Already Initialized.");

	if (!SDL_Init(SDL_INIT_VIDEO))
		log_critical("Cannot Initialize SDL::" + cstr_to_str(SDL_GetError()));

	is_init = true;

	log_info("The SDL was initialiazed.");
}

void sdl_ctx_destroy() 
{
	log_info("Quitting SDL...");

	if (!is_init)
		log_critical("\tCannot free the SDL memory::SDL is not Initialiazed.");

	SDL_Quit();

	is_init = false;

	log_info("SDL quit.");
}
