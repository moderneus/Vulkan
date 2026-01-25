#include "util/File.hpp"
#include "util/debug/Logger.hpp"

#include <fstream>

std::vector<char> read_file(const std::string& path) 
{
	log_info("Reading a File... Path = ", path);

	std::ifstream file(path, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		log_error("Failed to Open File by Path: ", path);
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();

	log_info("The File was Read by Path = ", path);

	return buffer;
}
