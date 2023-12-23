// define get_resources_dir() function
#ifndef GETPATH_H
#define GETPATH_H

// include head
#include "header.h"
// include consts
#include "myConst.h"

class sAppFunctions {
private:
    /* data */
public:
    sAppFunctions() { }
    ~sAppFunctions() { }
    // get path to resources folder

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
    void s(){
        
    }

    // get path to app directory
    static const std::string getDocumentsAppFolder()
    {
        struct passwd* pw = getpwuid(getuid());
        const char* homedir = pw->pw_dir;

        std::string appDirectory = std::string(homedir) + "/Documents/" + myConst::app_name;

        return appDirectory;
    }

    static void createAppDirectories(const std::string& appName)
    {
        // some system functions
        struct passwd* pw = getpwuid(getuid());
        const char* homedir = pw->pw_dir;

        // make str for path to app dir and create it
        std::string appDirectory = std::string(homedir) + "/Documents/" + appName;

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

    // check if app directory exists
    static const bool checkAppDirectoryExists(const std::string& appName)
    {
        struct passwd* pw = getpwuid(getuid());
        const char* homedir = pw->pw_dir;

        std::string appDirectory = std::string(homedir) + "/Documents/" + appName;

        return std::filesystem::exists(appDirectory);
    }
};
#endif