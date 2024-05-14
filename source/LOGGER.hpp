///////////////////////////////////////////////////////////////////////////////////////
#ifndef SOURCE_LOGGER_HPP_
#define SOURCE_LOGGER_HPP_

#include "systemFunctionUNIX.hpp"

// enum value for log
enum class logType {
    INFO = 0,
    WARNING = 1,
    ERROR = 2
};

class Logger {
private:
    std::ofstream logFile;

public:
    Logger()
    {
        logFile.open(ApplicationsFunctions::getDocumentsAppFolder() + "/" + "log.log", std::ios::app);
        if (!logFile) {
            std::cerr << "Logger: Unable to open the log file. Creating a new one." << std::endl;
            logFile.open(ApplicationsFunctions::getDocumentsAppFolder() + "/backup_" + "log.log", std::ios::app);
            if (!logFile) {
                throw std::runtime_error("Logger: Unable to open the backup log file");
            }
        }
    }
    ~Logger()
    {
        if (logFile) {
            logFile.close();
            // Создаем резервную копию лог-файла

            std::filesystem::copy(ApplicationsFunctions::getDocumentsAppFolder() + "/" + "log.log", ApplicationsFunctions::getDocumentsAppFolder() + "/backup_" + "log.log", std::filesystem::copy_options::overwrite_existing);
        }
    }

    static void log(const std::string& message, const std::string& source, logType level = logType::INFO)
    {
        std::array<std::string, 3> logTypes = {
            "INFO",
            "WARNING",
            "ERROR"
        };
        std::string typeString = logTypes[static_cast<int>(level)];

        std::string logEntry = "[" + ApplicationsFunctions::getCurrentTime() + "] _L: " + typeString + "\t_S: " + source + " -> " + message;
        std::ofstream logFile;
        logFile.open(ApplicationsFunctions::getDocumentsAppFolder() + "/" + "log.log", std::ios::app);
        if (!logFile) {
            std::cerr << "Logger: Unable to open the log file. Creating a new one." << std::endl;
            logFile.open(ApplicationsFunctions::getDocumentsAppFolder() + "/backup_" + "log.log", std::ios::app);
            if (!logFile) {
                throw std::runtime_error("Logger: Unable to open the backup log file");
            }
        }

        logFile << logEntry << std::endl;
        logFile.close();
    }
};

#endif // SOURCE_LOGGER_HPP_