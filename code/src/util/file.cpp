#include "util/file.hpp"
#include "util/debug/log.hpp"

#include <fstream>

std::vector<char> file_read(const std::string &path) 
{
	log_info("Reading the File by Path: ", path);

	std::ifstream f(path, std::ios::ate | std::ios::binary);

	if (!f.is_open())
		log_error("Failed to Open File by Path: ", path);

	size_t len = (size_t)f.tellg();
	std::vector<char> buf(len);

	f.seekg(0);
	f.read(buf.data(), len);
	f.close();

	log_info("The File was Read by Path: ", path);

	return buf;
}
