#pragma once

#include "core/objects/Instance.hpp"

namespace Engine
{
    namespace Core
    {
        class Core
        {
        private:    
            Instance vkInstance;
            
        public: 
            void init();
            void destroy();
            Instance& getInstance();
        };
    }
}
