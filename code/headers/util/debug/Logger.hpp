#pragma once

#include <string>
#include <vector>

enum Level { INFO, ERROR, CRITICAL, SUCCESS };
    
std::string log_get_time();

void log_open_file(const std::string& path);

void log_write(const Level level, const std::string& msg, const std::string& value);

void log_info(const std::string& msg);

void log_info(const std::string& msg, const std::string& value);

void log_info(const std::string& msg, const std::vector<std::string>& info);

void log_error(const std::string& msg);

void log_error(const std::string& msg, const std::string& error);

void log_critical(const std::string& msg);

void log_critical(const std::string& msg, const std::string& error);

void log_success(const std::string& msg);

void log_success(const std::string& msg, const std::string& value);
