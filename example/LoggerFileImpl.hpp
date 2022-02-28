
#ifndef LOGGER_FILE_IMPL_HPP
#define LOGGER_FILE_IMPL_HPP

#include <iostream>

#include "LoggerInterface.hpp"

class FileLogger : public ILogger
{
    public:
        ~FileLogger() {};

        void Log(const std::string& message) override
        {
            std::cout << "FileLogger: " << message << std::endl;
        }
};

#endif