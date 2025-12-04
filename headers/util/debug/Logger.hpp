#pragma once

#include "util/Singleton.hpp"

#include <fstream>
#include <string>
#include <vector>

namespace Engine 
{
    namespace Utils
    {
        class Logger : public Singleton<Logger>
        {
        private:
            friend class Singleton<Logger>;
            
            enum Level {INFO, ERROR, CRITICAL, SUCCESS};
            std::string path = "logs/log.txt";
            std::ofstream logf;
            
            void openLogFile(const std::string& path);
            void write(const Level level, const std::string& msg, const std::string& value);
            std::string currentDateTime();
            
            Logger();
            
        public: 
            void init();
            void info(const std::string& msg);
            void info(const std::string& msg, const std::string& value);
            void info(const std::string& msg, const std::vector<std::string>& info);
            void error(const std::string& msg);
            void critical(const std::string& msg);
            void success(const std::string& msg);
        };
    }
}
