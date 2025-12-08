#include "util/String.hpp"

std::vector<std::string> Engine::Utils::cstrVectorToStringVector(const std::vector<const char*> cstrs)
{
    std::vector<std::string> strs;
    
    for(const char* cstr : cstrs)
        strs.push_back(cstr);

    return strs;
}

std::string Engine::Utils::cstrToString(const char* cstr)
{
    std::string tmp = cstr;

    return tmp;
}