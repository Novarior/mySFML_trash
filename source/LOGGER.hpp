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

    static std::string getCurrentTime()
    {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
        return ss.str();
    }

public:
    Logger()
    {
        logFile.open(sAppFunctions::getDocumentsAppFolder() + "/" + "log.log", std::ios::app);
        if (!logFile) {
            std::cerr << "Logger: Unable to open the log file. Creating a new one." << std::endl;
            logFile.open(sAppFunctions::getDocumentsAppFolder() + "/backup_" + "log.log", std::ios::app);
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

            std::filesystem::copy(sAppFunctions::getDocumentsAppFolder() + "/" + "log.log", sAppFunctions::getDocumentsAppFolder() + "/backup_" + "log.log", std::filesystem::copy_options::overwrite_existing);
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

        std::string logEntry = "[" + getCurrentTime() + "] _L: " + typeString + "\t_S: " + source + " -> " + message;
        std::ofstream logFile;
        logFile.open(sAppFunctions::getDocumentsAppFolder() + "/" + "log.log", std::ios::app);
        if (!logFile) {
            std::cerr << "Logger: Unable to open the log file. Creating a new one." << std::endl;
            logFile.open(sAppFunctions::getDocumentsAppFolder() + "/backup_" + "log.log", std::ios::app);
            if (!logFile) {
                throw std::runtime_error("Logger: Unable to open the backup log file");
            }
        }

        logFile << logEntry << std::endl;
        logFile.close();
    }
};

#endif // SOURCE_LOGGER_HPP_