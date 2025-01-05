#ifndef SOURCE_LOGGER_HPP_
#define SOURCE_LOGGER_HPP_

#include "systemFunctionUNIX.hpp"
#include <array>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

// Типы логов
enum class logType {
    INFO = 0,
    WARNING = 1,
    ERROR = 2
};

class Logger {
private:
    std::ofstream logFile;
    std::string logPath;

    // Получение строки для типа лога
    static const std::string& logTypeToString(logType level)
    {
        static const std::array<std::string, 3> logTypes = { "INFO", "WARNING", "ERROR" };
        return logTypes[static_cast<int>(level)];
    }

    // Открытие файла лога с обработкой ошибок
    void openLogFile()
    {
        logPath = ApplicationsFunctions::getDocumentsAppFolder() + "/log.log";
        logFile.open(logPath, std::ios::app);

        if (!logFile) {
            std::cerr << "Logger: Unable to open the log file. Creating a new one." << std::endl;
            logFile.open(ApplicationsFunctions::getDocumentsAppFolder() + "/backup_log.log", std::ios::app);

            if (!logFile) {
                throw std::runtime_error("Logger: Unable to open both the main and backup log files.");
            }
        }
    }

    // Создание резервной копии лог-файла
    void backupLogFile()
    {
        try {
            std::string backupPath = ApplicationsFunctions::getDocumentsAppFolder() + "/backup_log.log";

            if (std::filesystem::exists(logPath)) {
                std::filesystem::copy(logPath, backupPath, std::filesystem::copy_options::overwrite_existing);
            }
        } catch (const std::exception& e) {
            std::cerr << "Logger: Failed to create a backup of the log file: " << e.what() << std::endl;
        }
    }

public:
    Logger()
    {
        openLogFile();
    }

    ~Logger()
    {
        if (logFile.is_open()) {
            logFile.close();
            backupLogFile();
        }
    }

    // Метод для записи лога
    void log(const std::string& message, const std::string& source, logType level = logType::INFO)
    {
        if (!logFile.is_open()) {
            openLogFile();
        }

        std::string logEntry = "[" + ApplicationsFunctions::getCurrentTime() + "] " + logTypeToString(level) + "\t" + "_S: " + source + " -> " + message;

        logFile << logEntry << std::endl;

        // Также выводим в консоль, если уровень лога - WARNING или ERROR
        if (level == logType::WARNING || level == logType::ERROR) {
            std::cerr << logEntry << std::endl;
        }
    }

    // Статический метод для записи лога без экземпляра
    static void logStatic(const std::string& message, const std::string& source, logType level = logType::INFO)
    {
        try {
            Logger logger;
            logger.log(message, source, level);
        } catch (const std::exception& e) {
            std::cerr << "Logger: Failed to log message: " << e.what() << std::endl;
        }
    }
};

#endif // SOURCE_LOGGER_HPP_