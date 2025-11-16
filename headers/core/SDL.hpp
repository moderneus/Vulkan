#pragma once

namespace Engine
{
    namespace Core
    {
        class SDL
        {
        private:
            bool isInit;
            
        public:    
            void init();
            void destroy();
        };
    }
}
