#include "util/String.hpp"

std::vector<std::string> cstr_vec_to_str_vec(const std::vector<const char*> &cstrs) 
{
	std::vector<std::string> strs;

	for(const char *cstr : cstrs){
		strs.push_back(cstr);
	}

	return strs;
}

std::string cstr_to_str(const char *cstr) 
{
	std::string str = cstr;
	return str;
}
