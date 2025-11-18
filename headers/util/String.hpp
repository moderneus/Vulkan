#pragma once

#include <string>
#include <vector>

namespace Engine
{
    namespace Utils
    {
        std::vector<std::string> cstrArrayToStringVector(const char* const* cstr, const size_t count);

        std::string cstrToString(const char* cstr);
    }
}
