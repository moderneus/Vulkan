#include "engine/Engine.hpp"

int main()
{
    Engine::Engine engine;

    engine.init();

    engine.run();

    engine.destroy();
}
