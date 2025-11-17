#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace Engine 
{
    namespace Utils
    {
        class Logger
        {
        private:
            enum Level {INFO, ERROR, CRITICAL, SUCCESS};
            std::string path = "logs/log.txt";
            std::ofstream logf;
            
            void openLogFile(const std::string& path);
            void write(const std::string& msg, const Level level);
            std::string currentDateTime();
            
            Logger& operator=(const Logger& other) = delete;
            Logger(const Logger& other) = delete;
            Logger();

        public: 
            static Logger* get();

            void info(const std::string& msg);
            void info(const std::string& msg, const std::vector<std::string>& info);
            void error(const std::string& msg);
            void critical(const std::string& msg);
            void success(const std::string& msg);
        };
    }
}

