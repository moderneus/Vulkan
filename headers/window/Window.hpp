#pragma once

#include <SDL3/SDL.h>

namespace Engine
{
    namespace Window
    {
        class Window
        {
        private:
            SDL_Window* pWindow = nullptr;
            bool isClosed = false;
            
        public:
            void create(const char* title, const unsigned int width, const unsigned int height);
            void destroy();
            void close();
            bool closed();
                
            SDL_Window* get();
        };
    }
}
