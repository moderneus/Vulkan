#include "gfx/Renderer.hpp"

int main()
{
    Renderer vkRenderer;

    vkRenderer.init();

    vkRenderer.draw();

    vkRenderer.destroy();
    
    return 0;
}
