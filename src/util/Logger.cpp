#include "util/Logger.hpp"

#include <filesystem>
#include <fmt/core.h>

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
            logf << "INFO::" << msg << std::endl;
        break;
            
        case ERROR:
            logf << "ERROR::" << msg << std::endl;
        break;

        case CRITICAL:
            logf << "CRITICAL::" << msg << std::endl;
            std::exit(-1);
        break;
            
        case SUCCESS:
            logf << "SUCCESS::" << msg << std::endl;
        break;
    }
    
    logf.flush();
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
