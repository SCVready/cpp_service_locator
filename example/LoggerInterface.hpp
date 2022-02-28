
#ifndef LOGGER_INTERFACE_HPP
#define LOGGER_INTERFACE_HPP

#include <string>

class ILogger
{
    public:
        virtual ~ILogger() {};

        virtual void Log(const std::string& message) = 0;
};

#endif
