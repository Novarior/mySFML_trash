#ifndef GETPATH_H
#define GETPATH_H

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#include <pwd.h>
#include <unistd.h>
#endif
#include "_myConst.h"

class ApplicationsFunctions {
private:
    /// @brief Создание директорий приложения в папке "Документы"
    static void createAppDirectories()
    {
        if (const char* homedir = getHomeDirectory()) {
            std::string appDirectory = std::string(homedir) + "/Documents/" + myConst::app_name;

            try {
                std::filesystem::create_directories(appDirectory + "/config");
            } catch (const std::filesystem::filesystem_error& e) {
                std::cerr << "Ошибка создания директорий: " << e.what() << std::endl;
            }
        } else {
            std::cerr << "Не удалось получить домашнюю директорию." << std::endl;
        }
    }

    /// @brief Получение пути к домашней директории
    /// @return Путь к домашней директории или `nullptr`, если не удалось
    static const char* getHomeDirectory()
    {
#ifdef __APPLE__
        struct passwd* pw = getpwuid(getuid());
        return pw ? pw->pw_dir : nullptr;
#else
        // Для других платформ можно использовать getenv("HOME")
        return std::getenv("HOME");
#endif
    }

public:
    ApplicationsFunctions() = default;
    ~ApplicationsFunctions() = default;

    /// @brief Получение пути к ресурсам приложения (только macOS)
    /// @return Путь к папке ресурсов
    static std::string get_resources_dir()
    {
#ifdef __APPLE__
        CFURLRef resourceURL = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
        if (!resourceURL) {
            std::cerr << "Не удалось получить путь к ресурсам." << std::endl;
            return "";
        }

        char resourcePath[PATH_MAX];
        if (!CFURLGetFileSystemRepresentation(resourceURL, true, reinterpret_cast<UInt8*>(resourcePath), PATH_MAX)) {
            CFRelease(resourceURL);
            std::cerr << "Не удалось преобразовать путь к ресурсам." << std::endl;
            return "";
        }

        CFRelease(resourceURL);
        return resourcePath;
#else
        return ""; // Реализация для других платформ
#endif
    }

    /// @brief Получение пути к директории приложения в "Документах"
    /// @return Путь к папке приложения
    static std::string getDocumentsAppFolder()
    {
        if (const char* homedir = getHomeDirectory()) {
            return std::string(homedir) + "/Documents/" + myConst::app_name;
        }
        return "";
    }

    /// @brief Проверка существования директорий приложения
    /// @return `true`, если директории существуют, иначе создаёт их
    static bool checkAppDirectoryExists()
    {
        std::string appDirectory = getDocumentsAppFolder() + "/config";

        if (std::filesystem::exists(appDirectory)) {
            return true;
        }

        createAppDirectories();
        return std::filesystem::exists(appDirectory);
    }

    /// @brief Получение текущего времени в формате "YYYY-MM-DD HH:MM:SS"
    /// @return Строка с текущим временем
    static std::string getCurrentTime()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
        return ss.str();
    }
};

#endif // GETPATH_H