#include "systemFunctionUNIX.hpp"

// get path to resources folder
std::string get_resources_dir()
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

// get path to app directory
std::string get_doc_app_dir()
{
    struct passwd* pw = getpwuid(getuid());
    const char* homedir = pw->pw_dir;

    std::string appDirectory = std::string(homedir) + "/Documents/" + myConst::app_name;

    return appDirectory;
}

void createAppDirectoryAndConfigSubdirectory(const std::string& appName)
{
    struct passwd* pw = getpwuid(getuid());
    const char* homedir = pw->pw_dir;

    std::string appDirectory = std::string(homedir) + "/Documents/" + appName;
    std::filesystem::create_directories(appDirectory);

    if (!std::filesystem::exists(appDirectory)) {
        std::cout << "Failed to create directory: " << appDirectory << std::endl;
        return;
    }

    std::string configSubdirectory = appDirectory + "/config";
    std::filesystem::create_directories(configSubdirectory);

    if (!std::filesystem::exists(configSubdirectory)) {
        std::cout << "Failed to create subdirectory: " << configSubdirectory << std::endl;
    }
}

// check if app directory exists
bool checkAppDirectoryExists(const std::string& appName)
{
    struct passwd* pw = getpwuid(getuid());
    const char* homedir = pw->pw_dir;

    std::string appDirectory = std::string(homedir) + "/Documents/" + appName;

    return std::filesystem::exists(appDirectory);
}