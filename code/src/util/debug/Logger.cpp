#include "util/debug/Logger.hpp"

#include "fmt/core.h"

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
	oss << '[' << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] ";

	return oss.str();
}

void log_open_file(const std::string& path) 
{
	log_file.open(path, std::ios::app);

	if (!log_file.is_open()) {
		fmt::print("Failed to open file by path: {}\n", path);
	}
}

void log_write(const Level level, const std::string& msg, const std::string& value="") 
{
	std::filesystem::create_directories("logs");
	log_open_file(path);

	switch(level) {
		case INFO:
			log_file << log_get_time() << "\tINFO::" << msg << value << std::endl;
		break;
		    
		case ERROR:
			log_file << log_get_time() << "\tERROR::" << msg << value << std::endl;
		break;

		case CRITICAL:
			log_file << log_get_time() << "\tCRITICAL::" << msg << value << std::endl;
			std::abort();
		break;
		    
		case SUCCESS:
			log_file << log_get_time() << "\tSUCCESS::" << msg << value << std::endl;
		break;
	}

	log_file.flush();
	log_file.close();
}

void log_info(const std::string& msg) 
{
	log_write(INFO, msg);
}

void log_info(const std::string& msg, const std::string& value) 
{
	log_write(INFO, msg, value);
}

void log_info(const std::string& msg, const std::vector<std::string>& info) 
{
	std::string tmp = msg;

	for(const auto& s : info) {
		tmp += s + " ";
	}

	log_write(INFO, tmp);
}
    
void log_error(const std::string& msg) 
{
	log_write(ERROR, msg);
}

void log_error(const std::string& msg, const std::string& error) 
{
	log_write(ERROR, msg, error);
}

void log_critical(const std::string& msg) 
{
	log_write(CRITICAL, msg);
}

void log_critical(const std::string& msg, const std::string& error) 
{
	log_write(CRITICAL, msg, error);
}

void log_success(const std::string& msg) 
{
	log_write(SUCCESS, msg);
}

void log_success(const std::string& msg, const std::string& value) 
{
	log_write(SUCCESS, msg, value);
}
