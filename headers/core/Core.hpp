#pragma once

#include "core/objects/Instance.hpp"

class Core
{
private:    
    Instance vkInstance;
    
public: 
    void init();
    void destroy();
    Instance& getInstance();
};
