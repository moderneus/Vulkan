#include "engine/Engine.hpp"

int main() {
    Engine engine;
    engine_init(&engine);
    engine_run(&engine);
    engine_destroy(&engine);
}
