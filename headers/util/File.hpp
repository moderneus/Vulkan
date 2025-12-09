#pragma once

#include <vector>
#include <string>

namespace Engine
{
    namespace Utils
    {
        std::vector<char> readFile(const std::string& path);
    }
}