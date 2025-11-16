#include "util/String.hpp"

std::vector<std::string> cstrArrayToVector(const char* const* cstr, const size_t count)
{
    std::vector<std::string> strs;
    
    for(size_t i = 0; i < count; ++i)
        strs.push_back(cstr[i]);

    return strs;
}

std::string cstrToString(const char* cstr)
{
    std::string tmp = cstr;

    return tmp;
}
