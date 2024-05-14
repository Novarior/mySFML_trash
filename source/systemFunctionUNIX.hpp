// define get_resources_dir() function
#ifndef GETPATH_H
#define GETPATH_H

// include head
// system include
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#include <pwd.h>
#endif
// include consts
#include "myConst.h"

class ApplicationsFunctions {
private:
    /// @brief create app directory in documents folder
    static void createAppDirectories()
    {
        // some system functions
        struct passwd* pw = getpwuid(getuid());
        const char* homedir = pw->pw_dir;

        // make str for path to app dir and create it
        std::string appDirectory = std::string(homedir) + "/Documents/" + myConst::app_name;

        // Function to create directory and handle errors
        auto createDirectory = [](const std::string& directoryPath) {
            bool isCreated = std::filesystem::create_directories(directoryPath);
            if (!isCreated && !std::filesystem::exists(directoryPath)) {
                std::cerr << "Failed to create directory: " << directoryPath << std::endl;
            }
        };

        createDirectory(appDirectory);
        createDirectory(appDirectory + "/config");
    }

public:
    ApplicationsFunctions() { }
    ~ApplicationsFunctions() { }

    // get path to resources folder from out application bundle
    static const std::string get_resources_dir()
    {
        CFURLRef resourceURL = CFBundleCopyResourcesDirectoryURL(CFBundleGetMainBundle());
        char resourcePath[PATH_MAX];
        if (CFURLGetFileSystemRepresentation(resourceURL, true, (UInt8*)resourcePath, PATH_MAX)) {
            if (resourceURL != NULL) {
                CFRelease(resourceURL);
            }
            return resourcePath;
        }
        return "";
    }
    void s()
    {
    }

    /// @brief return path to app directory to documents folder
    /// @return     path to app directory
    static const std::string getDocumentsAppFolder()
    {
        struct passwd* pw = getpwuid(getuid());
        const char* homedir = pw->pw_dir;

        std::string appDirectory = std::string(homedir) + "/Documents/" + myConst::app_name;

        return appDirectory;
    }

    /// @brief Check if app directory exists
    /// @return true if app directory exists
    static const bool checkAppDirectoryExists()
    {
        struct passwd* pw = getpwuid(getuid());
        const char* homedir = pw->pw_dir;

        std::string appDirectory = std::string(homedir) + "/Documents/" + myConst::app_name + "/config";

        if (std::filesystem::exists(appDirectory))
            return true;
        else {
            createAppDirectories();
            return false;
        }
    }

    static std::string getCurrentTime()
    {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
        return ss.str();
    }
};
#endif