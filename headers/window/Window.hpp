#pragma once

#include "SDL3/SDL_video.h"

namespace Engine
{
    namespace Window
    {
        class Window
        {
        private:
            static SDL_Window* pWindow;
            static int w;
            static int h;

            bool isClosed = false;
            
        public:
            void create(const char* title, const unsigned int width, const unsigned int height);
            void destroy();
            void close();
            bool closed();
                
            static SDL_Window* get();
            static int width();
            static int height();
        };
    }
}
