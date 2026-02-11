#ifndef MOD_WINDOW_HPP
#define MOD_WINDOW_HPP

#include "SDL3/SDL_video.h"

struct window_t 
{
	SDL_Window*	handle	  = nullptr;
	uint32_t	width     = 640;
	uint32_t	height	  = 480;
	bool		is_closed = false;
};

void win_create(window_t *win, const char *title, const uint32_t w, const uint32_t h);

void win_destroy(const window_t &win);

#endif
