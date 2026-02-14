#include "util/File.hpp"
#include "util/debug/Logger.hpp"

#include <fstream>

std::vector<char> file_read(const std::string &path) 
{
	log_info("Reading a File... Path = ", path);

	std::ifstream f(path, std::ios::ate | std::ios::binary);

	if (!f.is_open()) {
		log_error("Failed to Open File by Path: ", path);
	}

	size_t size = (size_t)f.tellg();
	std::vector<char> buf(size);

	f.seekg(0);
	f.read(buf.data(), size);
	f.close();

	log_info("The File was Read by Path = ", path);

	return buf;
}
