#include "gfx/Renderer.hpp"

int main()
{
    Engine::gfx::Renderer vkRenderer;

    vkRenderer.init();

    vkRenderer.draw();

    vkRenderer.destroy();
    
    return 0;
}
