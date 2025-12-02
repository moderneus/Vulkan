#include "util/String.hpp"

namespace Engine
{
    namespace Utils 
    {
        std::vector<std::string> cstrVectorToStringVector(const std::vector<const char*> cstrs)
        {
            std::vector<std::string> strs;
            
            for(const char* cstr : cstrs)
                strs.push_back(cstr);

            return strs;
        }

        std::string cstrToString(const char* cstr)
        {
            std::string tmp = cstr;

            return tmp;
        }
    }
}