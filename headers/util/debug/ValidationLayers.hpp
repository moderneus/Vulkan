#pragma once

#include <vector>

namespace Engine
{
    namespace Utils
    {
        class ValidationLayers
        {
        private: 
            static const std::vector<const char*> validationLayers;
            bool debugging = false;
            
        public:
            static const std::vector<const char*>& get();
            void enable();
            bool enabled();
            bool checkSupport();
        };
    }
}
