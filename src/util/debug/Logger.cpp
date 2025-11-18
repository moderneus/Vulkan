#include "util/debug/Logger.hpp"

#include <fmt/core.h>

#include <filesystem>
#include <chrono>
#include <sstream>
#include <iomanip>

Engine::Utils::Logger::Logger()
{
    std::filesystem::create_directories("logs");
    openLogFile(path);
}

Engine::Utils::Logger* Engine::Utils::Logger::get()
{
    static Logger instance;
    return &instance;
}

void Engine::Utils::Logger::openLogFile(const std::string& path)
{
    logf.open(path, std::ios::app);
    
    if(!logf.is_open())
        fmt::print("Failed to open file by path: {}\n", path);
}

void Engine::Utils::Logger::write(const std::string& msg, const Level level)
{
    switch(level)
    {
        case INFO:
            logf << currentDateTime() << "INFO::" << msg << std::endl;
        break;
            
        case ERROR:
            logf << currentDateTime() << "ERROR::" << msg << std::endl;
        break;

        case CRITICAL:
            logf << currentDateTime() << "CRITICAL::" << msg << std::endl;
            std::exit(-1);
        break;
            
        case SUCCESS:
            logf << currentDateTime() << "SUCCESS::" << msg << std::endl;
        break;
    }
    
    logf.flush();
}

std::string Engine::Utils::Logger::currentDateTime()
{
    auto now = std::chrono::system_clock::now();

    std::time_t t = std::chrono::system_clock::to_time_t(now);

    std::tm tm = {};

    localtime_r(&t, &tm);

    std::ostringstream oss;
    oss << '[' << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] ";

    return oss.str();
}

void Engine::Utils::Logger::info(const std::string& msg)
{
    write(msg, INFO);
}

void Engine::Utils::Logger::info(const std::string& msg, const std::vector<std::string>& info)
{
    std::string tmp = msg;
    
    for(size_t i = 0; i < info.size(); ++i)
        tmp += info[i] + " ";

    write(tmp, INFO);
}
    
void Engine::Utils::Logger::error(const std::string& msg)
{
    write(msg, ERROR);
}

void Engine::Utils::Logger::critical(const std::string& msg)
{
    write(msg, CRITICAL);
}

void Engine::Utils::Logger::success(const std::string& msg)
{
    write(msg, SUCCESS);
}
