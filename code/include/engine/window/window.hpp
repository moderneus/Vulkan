#ifndef MOD_WINDOW_HPP
#define MOD_WINDOW_HPP

#include "SDL3/SDL_video.h"

struct window {
	SDL_Window		*handle	   = nullptr;
	uint32_t		 width     = 640;
	uint32_t		 height	   = 480;
	bool			 is_closed = false;
};

void window_create(window *win, const char *title, const uint32_t w, const uint32_t h);

void window_destroy(const window &win);

#endif
