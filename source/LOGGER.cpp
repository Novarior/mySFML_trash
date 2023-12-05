#include "LOGGER.hpp"

std::string Logger::getCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

Logger::Logger()
{
    logFile.open(get_doc_app_dir() + "/" + fileName, std::ios::app);
    if (!logFile) {
        std::cerr << "Logger: Unable to open the log file. Creating a new one." << std::endl;
        logFile.open(get_doc_app_dir() + "/backup_" + fileName, std::ios::app);
        if (!logFile) {
            throw std::runtime_error("Logger: Unable to open the backup log file");
        }
    }
}

Logger::~Logger()
{
    if (logFile) {
        logFile.close();
        // Создаем резервную копию лог-файла

        std::filesystem::copy(get_doc_app_dir() + "/" + fileName, get_doc_app_dir() + "/backup_" + fileName, std::filesystem::copy_options::overwrite_existing);
    }
}

void Logger::log(const std::string& message, const std::string& source, bool success, int level)
{
    std::string successString = success ? "Success" : "Failure";
    std::string logEntry = "[" + getCurrentTime() + "]  _L: " + std::to_string(level) + "  " + successString + "  " + source + "  ->  " + message;
    logFile << logEntry << std::endl;
}