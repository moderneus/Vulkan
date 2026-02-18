#ifndef MOD_RENDERER_HPP
#define MOD_RENDERER_HPP

#include <cstdint>

struct event_manager;
struct window;
struct core;

struct renderer {
	window *pwin;
};

struct renderer_state {
	uint32_t frame = 0;
	bool fb_resized = false;
};

void renderer_init(renderer *r, window *win);

void renderer_destroy(renderer *r);

void renderer_loop(renderer *r, event_manager *ev_m, core *c);

void renderer_draw(const renderer &r, renderer_state *st, core *c);

#endif
