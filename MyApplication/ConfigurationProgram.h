#ifndef CFG_PROG
#define CFG_PROG


#define TRY_VERSION_MAJOR 0
#define TRY_VERSION_MINOR 0
#define TRY_VERSION_PATCH 1

//here the behavior of the program is implemented at the preprocessor level
const char versionApp[] = "v0.0.1";

#if defined(_WIN32)
const char OperationSystem[] = "Windows OS";

#elif defined(__APPLE__)
const char OperationSystem[] = "MacOSX";

#else

#error This operating system is not supported this program

#endif

#endif