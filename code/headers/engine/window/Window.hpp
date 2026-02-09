#ifndef MOD_WINDOW_HPP
#define MOD_WINDOW_HPP

#include "SDL3/SDL_video.h"

struct window_t 
{
	SDL_Window*	phandle	  = nullptr;
	uint32_t	width     = 640;
	uint32_t	height	  = 480;
	bool		is_closed = false;
};

void window_create(window_t* window, const char* title, const uint32_t width, const uint32_t height);

void window_destroy(const window_t& window);

#endif
