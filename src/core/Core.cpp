#include "core/Core.hpp"

void Core::init()
{
    vkInstance.create();
}

void Core::destroy()
{
    vkInstance.destroy();
}

Instance& Core::getInstance()
{
    return vkInstance;
}
