
#ifndef LOGGER_NETWORK_IMPL_HPP
#define LOGGER_NETWORK_IMPL_HPP

#include <iostream>

#include "LoggerInterface.hpp"

class NetworkLogger : public ILogger
{
    public:
        ~NetworkLogger() {};

        void Log(const std::string& message) override
        {
            std::cout << "NetworkLogger: " << message << std::endl;
        }
};

#endif
