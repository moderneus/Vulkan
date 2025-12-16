#include "gfx/Renderer.hpp"
#include "util/EventManager.hpp"
#include "util/debug/Logger.hpp"

void renderer_init(Renderer* renderer, Window* pwindow) {
    log_info("Initializing a Renderer...");
    renderer->pwindow = pwindow;
    log_success("The Renderer was Initialized!");
}

void renderer_destroy(Renderer* renderer) {
    log_info("Destroying the Renderer...");
    renderer->pwindow = nullptr;
    log_success("The Renderer was Destroyed!");
}

void renderer_loop(Renderer* renderer) {
    while(!renderer->pwindow->is_closed) {
        event_manager_poll_events(&renderer->event_manager, renderer->pwindow);
    }
}

void renderer_draw(Renderer* renderer) {
    renderer_loop(renderer);
}
