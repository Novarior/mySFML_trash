#ifndef CFG_PROG
#define CFG_PROG
#include "cmakever.h"

//here the behavior of the program is implemented at the preprocessor level
const char versionApp = char(CMAKE_PROJECT_VERSION_PATCH);


#if defined(_WIN32)
const char OperationSystem[] = "Windows OS";

#elif defined(__APPLE__)
const char OperationSystem[] = "MacOSX";

#else
const char OperationSystem[] = "UNDEFINED";
#error This operating system is not supported this program

#endif

#endif