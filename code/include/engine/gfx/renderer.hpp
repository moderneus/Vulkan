#ifndef MOD_RENDERER_HPP
#define MOD_RENDERER_HPP

#include <cstdint>

struct event_manager_t;
struct window_t;
struct core_t;

struct renderer_t
{
	window_t *pwin;
};

struct renderer_state_t
{
	uint32_t frame = 0;
	bool fb_resized = false;
};

void rndr_init(renderer_t *r, window_t *win);

void rndr_destroy(renderer_t *r);

void rndr_loop(renderer_t *r, event_manager_t *ev_m, core_t *core);

void rndr_draw(const renderer_t &r, renderer_state_t *st, core_t *core);

#endif
