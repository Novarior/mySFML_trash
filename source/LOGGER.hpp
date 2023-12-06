///////////////////////////////////////////////////////////////////////////////////////
#ifndef SOURCE_LOGGER_HPP_
#define SOURCE_LOGGER_HPP_

#include "systemFunctionUNIX.hpp"
// static member


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
        logFile.open(sAppFunctions::get_doc_app_dir() + "/" + "log.log", std::ios::app);
        if (!logFile) {
            std::cerr << "Logger: Unable to open the log file. Creating a new one." << std::endl;
            logFile.open(sAppFunctions::get_doc_app_dir() + "/backup_" + "log.log", std::ios::app);
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

            std::filesystem::copy(sAppFunctions::get_doc_app_dir() + "/" + "log.log", sAppFunctions::get_doc_app_dir() + "/backup_" + "log.log", std::filesystem::copy_options::overwrite_existing);
        }
    }

    static void log(const std::string& message, const std::string& source, bool success, int level)
    {
        std::string successString = success ? "Success" : "Failure";
        std::string logEntry = "[" + getCurrentTime() + "]  _L: " + std::to_string(level) + "  " + successString + "  " + source + "  ->  " + message;

        std::ofstream logFile;
        logFile.open(sAppFunctions::get_doc_app_dir()  + "/" + "log.log", std::ios::app);
        if (!logFile) {
            std::cerr << "Logger: Unable to open the log file. Creating a new one." << std::endl;
            logFile.open(sAppFunctions::get_doc_app_dir() + "/backup_" + "log.log", std::ios::app);
            if (!logFile) {
                throw std::runtime_error("Logger: Unable to open the backup log file");
            }
        }

        logFile << logEntry << std::endl;
        logFile.close();
    }
};

#endif // SOURCE_LOGGER_HPP_