#include "util/debug/Logger.hpp"

#include "fmt/core.h"

#include <ctime>
#include <filesystem>
#include <chrono>
#include <sstream>
#include <iomanip>

Engine::Utils::Logger::Logger()
{
    std::filesystem::create_directories("logs");
    openLogFile(path);
}

void Engine::Utils::Logger::openLogFile(const std::string& path)
{
    logf.open(path, std::ios::app);
    
    if(!logf.is_open())
        fmt::print("Failed to open file by path: {}\n", path);
}

void Engine::Utils::Logger::write(const Level level, const std::string& msg, const std::string& value="")
{
    switch(level)
    {
        case INFO:
            logf << currentDateTime() << "INFO::" << msg << value << std::endl;
        break;
            
        case ERROR:
            logf << currentDateTime() << "ERROR::" << msg << value << std::endl;
        break;

        case CRITICAL:
            logf << currentDateTime() << "CRITICAL::" << msg << value << std::endl;
            std::exit(-1);
        break;
            
        case SUCCESS:
            logf << currentDateTime() << "SUCCESS::" << msg << value << std::endl;
        break;
    }
    
    logf.flush();
}

std::string Engine::Utils::Logger::currentDateTime()
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

void Engine::Utils::Logger::info(const std::string& msg)
{
    write(INFO, msg);
}

void Engine::Utils::Logger::info(const std::string& msg, const std::string& value)
{
    write(INFO, msg, value);
}

void Engine::Utils::Logger::info(const std::string& msg, const std::vector<std::string>& info)
{
    std::string tmp = msg;
    
    for(const auto& s : info)
        tmp += s + " ";

    write(INFO, tmp);
}
    
void Engine::Utils::Logger::error(const std::string& msg)
{
    write(ERROR, msg);
}

void Engine::Utils::Logger::critical(const std::string& msg)
{
    write(CRITICAL, msg);
}

void Engine::Utils::Logger::critical(const std::string& msg, const std::string& error)
{
    write(CRITICAL, msg, error);
}

void Engine::Utils::Logger::success(const std::string& msg)
{
    write(SUCCESS, msg);
}