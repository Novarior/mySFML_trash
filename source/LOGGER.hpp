///////////////////////////////////////////////////////////////////////////////////////
#ifndef SOURCE_LOGGER_HPP_
#define SOURCE_LOGGER_HPP_

#include "header.h"

class Logger {
private:
    std::ofstream logFile;
    std::string fileName = "log.log";

    std::string getCurrentTime();

public:
    Logger();
    ~Logger();

    void log(const std::string& message, const std::string& source, bool success, int level = 0);
};

#endif // SOURCE_LOGGER_HPP_