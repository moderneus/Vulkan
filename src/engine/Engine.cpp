#include "engine/Engine.hpp"
#include "core/Core.hpp"
#include "core/SDL.hpp"
#include "util/debug/Logger.hpp"

void engine_init(Engine* engine) {
    log_info("Initializing Engine...");
    SDL_context_init();
    window_create(&engine->window, "Vulkan", 640, 480);
    vk_core_init();
    renderer_init(&engine->renderer);
    log_success("Engine was Initialized!");
}

void engine_destroy(Engine* engine) {
    log_info("Destroying Engine...");
    renderer_destroy(&engine->renderer);
    vk_core_destroy();
    window_destroy();
    SDL_context_destroy();
    log_success("Engine was Destroyed!");
}

void engine_run(const Engine& engine) {
    renderer_draw(engine.renderer);
}
