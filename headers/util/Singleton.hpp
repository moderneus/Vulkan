#pragma once

namespace Engine
{
    namespace Utils
    {
        template<class T>
        class Singleton
        {
        protected:
            Singleton() = default;
            Singleton(const Singleton& other) = delete;
            Singleton& operator=(const Singleton& other) = delete;
            
        public:
            static T* get()
            {
                static T instance;
                return &instance;
            }
        };
    }
}
