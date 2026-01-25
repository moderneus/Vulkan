#include "core/SDL/SDL.hpp"
#include "util/String.hpp"
#include "util/debug/Logger.hpp"

#include "SDL3/SDL_init.h"

bool is_init = false;

void SDL_context_init() 
{
	log_info("Initializing the SDL...");

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		log_critical("Cannot Initialize SDL::" + cstr_to_str(SDL_GetError()));
	}

	is_init = true;

	log_info("The SDL was initialiazed.");
}

void SDL_context_destroy() 
{
	log_info("Quitting SDL...");

	if (!is_init) {
		log_critical("Cannot free the SDL memory::SDL is not Initialiazed.");
	}

	SDL_Quit();

	is_init = false;

	log_info("SDL quit.");
}
