#pragma once

namespace Engine
{
    namespace Core
    {
        class SDL
        {
        private:
            bool isInit = false;
            
        public:    
            void init();
            void destroy();
        };
    }
}
