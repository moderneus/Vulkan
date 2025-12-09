#include "util/File.hpp"
#include "util/debug/Logger.hpp"

#include <fstream>

std::vector<char> Engine::Utils::readFile(const std::string& path)
{
    std::ifstream file(path, std::ios::ate | std::ios::binary);

    if(!file.is_open())
        Logger::get()->error("Failed to Open File by Path: ", path);

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);
    
    file.close();

    return buffer;
}