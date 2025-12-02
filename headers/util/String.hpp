#pragma once

#include <string>
#include <vector>

namespace Engine
{
    namespace Utils
    {
        std::vector<std::string> cstrVectorToStringVector(const std::vector<const char*> cstrs);

        std::string cstrToString(const char* cstr);
    }
}