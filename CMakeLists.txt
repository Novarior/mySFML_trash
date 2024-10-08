#set minimun cmake version for build 
cmake_minimum_required(VERSION 3.5.0)
project(Ekzeckt VERSION 0.0.7)

#set miniimum c++ standart 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_OSX_SYSROOT /Library/Developer/CommandLineTools/SDKs/MacOSX15.0.sdk)

#set build type

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Debug) 
else()
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Bundle)
endif()

message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message("CMAKE_PROJECT_VERSION = ${CMAKE_PROJECT_VERSION}")
message("Debug build = ${CMAKE_BUILD_TYPE}")

#include all files for build project
file(GLOB_RECURSE SOURCE_PROJECT_FILES source/*.cpp)


#include SFML library on project
message("")
find_package(SFML 2.6.1 COMPONENTS graphics window system audio REQUIRED)
message("SFML was found = ${SFML_FOUND}")

#find nlohmann json library
find_package(nlohmann_json 3.11.2 REQUIRED)
if(NOT nlohmann_json_FOUND)
    message("nlohmann_json was not found = ${nlohmann_json_FOUND}")
else()
    message("nlohmann_json was not found = ${nlohmann_json_FOUND}")
endif()

#for bundle
find_library(COREFOUNDATION_LIBRARY CoreFoundation "${CMAKE_OSX_SYSROOT}/System/Library/Frameworks")
if (NOT COREFOUNDATION_LIBRARY)
    message(FATAL_ERROR "CoreFoundation not found")
endif()
message("CoreFoundation = ${COREFOUNDATION_LIBRARY}" )
message("")

#search for all files in resources folder
file(GLOB_RECURSE MY_APP_RESOURCES source/res/*)
#loop for all files in resources folder
foreach(file IN LISTS MY_APP_RESOURCES)
    file(RELATIVE_PATH relative_path ${CMAKE_CURRENT_SOURCE_DIR}/source/res ${file})
    get_filename_component(dir ${relative_path} DIRECTORY)
    set_source_files_properties(${file} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/${dir}")
endforeach()

#meta data for bundle
set(METADATA_DIR ${CMAKE_SOURCE_DIR}/metadata)
set(MY_APP_ICON ${CMAKE_SOURCE_DIR}/metadata/ico.png)
set_source_files_properties(${myApp_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

#make a cmakever.h from template file and include on build
set(Template_ver metadata/cmakever.h.in )
configure_file(${Template_ver} ${CMAKE_CURRENT_BINARY_DIR}/../source/cmakever.h)

if(APPLE)
#Configure plist file for bundle
set(DATA_BUNDLE_BUNDLE_NAME "Ekzeckt")
set(DATA_BUNDLE_GUI_IDENTIFIER "com.ekzeckt")
set(DATA_BUNDLE_COPYRIGHT "© 2023 GitHub: Novarior")
set(DATA_BUNDLE_INFO_STRING "Ekzeckt")
set(DATA_BUNDLE_BUNDLE_VERSION "${CMAKE_PROJECT_VERSION}")
string(CONCAT DATA_BUNDLE_SHORT_VERSION_STRING "v" ${CMAKE_PROJECT_VERSION_MINOR} "." ${CMAKE_PROJECT_VERSION_PATCH})


set(DATA_BUNDLE_ICON_NAME "ico.png")
set(DATA_BUNDLE_ICON_FILE ${CMAKE_SOURCE_DIR}/metadata/ico.png)

configure_file(${METADATA_DIR}/Info.plist.in ${CMAKE_CURRENT_SOURCE_DIR}/bin/Info.plist)

##build bundle for macos

    add_executable(Ekzeckt MACOSX_BUNDLE ${SOURCE_PROJECT_FILES} ${MY_APP_RESOURCES} ${Template_ver} ${DATA_BUNDLE_ICON_FILE})
#check for debug or release build
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(Ekzeckt PUBLIC -g)
    else()
        target_compile_options(Ekzeckt PUBLIC -O3)
    endif() 

    target_link_libraries(Ekzeckt sfml-graphics sfml-window sfml-system sfml-audio)
    target_link_libraries(Ekzeckt nlohmann_json::nlohmann_json)
    target_link_libraries(Ekzeckt "-framework CoreFoundation")
    set_source_files_properties(${DATA_BUNDLE_ICON_FILE} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

    set_target_properties(Ekzeckt PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/bin/Info.plist)
    endif()
    
    set(CPACK_SOURCE_GENERATOR "DragNDrop")
    set(CPACK_GENERATOR "DragNDrop")


    include(InstallRequiredSystemLibraries)
    include(CPack)