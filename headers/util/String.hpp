#pragma once

#include <string>
#include <vector>

std::vector<std::string> cstrArrayToVector(const char* const* cstr, const size_t count);

std::string cstrToString(const char* cstr);
