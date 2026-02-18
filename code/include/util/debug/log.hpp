#ifndef MOD_LOG_HPP
#define MOD_LOG_HPP

#include <string>
#include <vector>

enum level { INFO, ERROR, CRITICAL };
    
std::string log_get_time();

void log_write(const level lvl, const std::string &msg, const std::string &val);

void log_info(const std::string &msg);

void log_info(const std::string &msg, const std::string &val);

void log_info(const std::string &msg, const std::vector<std::string> &info);

void log_error(const std::string &msg);

void log_error(const std::string &msg, const std::string &err);

void log_critical(const std::string &msg);

void log_critical(const std::string &msg, const std::string &err);

void log_init();

void log_destroy();

#endif
