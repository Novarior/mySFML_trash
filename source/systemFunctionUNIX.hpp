// define get_resources_dir() function
#ifndef GETPATH_H
#define GETPATH_H

#include "header.h"

// get path to resources folder
std::string get_resources_dir();

//get path to app directory
std::string get_app_dir();

// create app directory and config subdirectory
void createAppDirectoryAndConfigSubdirectory(const std::string& appName);

// check if app directory exists
bool checkAppDirectoryExists(const std::string& appName);

#endif