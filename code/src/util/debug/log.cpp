#include "util/debug/log.hpp"

#include "fmt/core.h"
#include "fmt/color.h"

#include <ctime>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <sstream>
#include <iomanip>

std::string path = "logs/log.txt";
std::ofstream log_file;

std::string log_get_time() 
{
	auto now = std::chrono::system_clock::now();
	std::time_t t = std::chrono::system_clock::to_time_t(now);

	std::tm tm = {};

#ifdef __WIN32__
	localtime_s(&tm, &t);
#endif 

#ifdef __linux__
	localtime_r(&t, &tm);
#endif

	std::ostringstream oss;
	oss << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "]";

	return oss.str();
}

void log_write(const level lvl, const std::string &msg, const std::string &val="") 
{
	switch(lvl) {
	case INFO:
		log_file << log_get_time() << " [INFO] " << msg << val << std::endl;
	break;
	    
	case ERROR:
		log_file << log_get_time() << " [ERROR] " << msg << val << std::endl;
	break;

	case CRITICAL:
		log_file << log_get_time() << " [CRITICAL] " << msg << val << std::endl;
		std::abort();
	break;
	}
	log_file.flush();
}

void log_info(const std::string &msg) 
{
	log_write(INFO, msg);
}

void log_info(const std::string &msg, const std::string &val) 
{
	log_write(INFO, msg, val);
}

void log_info(const std::string &msg, const std::vector<std::string> &info) 
{
	std::string tmp = msg;

	for(const auto &str : info)
		tmp += str + " ";

	log_write(INFO, tmp);
}
    
void log_error(const std::string &msg) 
{
	log_write(ERROR, msg);
}

void log_error(const std::string &msg, const std::string &err) 
{
	log_write(ERROR, msg, err);
}

void log_critical(const std::string &msg) 
{
	log_write(CRITICAL, msg);
}

void log_critical(const std::string &msg, const std::string &err) 
{
	log_write(CRITICAL, msg, err);
}

void log_init() 
{
	std::filesystem::create_directories("logs");
	log_file.open(path, std::ios::app);

	if (!log_file.is_open())
		fmt::print(fmt::fg(fmt::color::red), "\t[ERROR]\tFailed to open file by path: {}\n", path);
	else
		log_write(INFO, "The Logger was Initialized.");
	
}

void log_destroy()
{
	log_file.close();
}
