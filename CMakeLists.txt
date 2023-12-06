#set minimun cmake version for build 
cmake_minimum_required(VERSION 3.5.0)
project(Ekzeckt VERSION 0.0.6)

#set miniimum c++ standart 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set build type
message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message("CMAKE_PROJECT_VERSION = ${CMAKE_PROJECT_VERSION}")

#include all files for build project
file(GLOB_RECURSE SOURCE_PROJECT_FILES source/*.cpp)

#set outputs directorry
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Bundle) 

# chek operation system
if(WIN32)
    set(OPERATION_SYSTEM "Windows")
elseif(APPLE)
    set(OPERATION_SYSTEM "MacOS")
elseif(UNIX)
    set(OPERATION_SYSTEM "Unix")
else()
    set(OPERATION_SYSTEM "Other")
endif()

#include SFML library on project
find_package(SFML 2.6.1 COMPONENTS graphics system window REQUIRED)
#for bundle
file(GLOB_RECURSE MY_APP_RESOURCES bin/resources/*)
find_library(COREFOUNDATION_LIBRARY CoreFoundation)


foreach(file IN LISTS MY_APP_RESOURCES)
file(RELATIVE_PATH relative_path ${CMAKE_CURRENT_SOURCE_DIR}/bin/resources ${file})
get_filename_component(dir ${relative_path} DIRECTORY)
set_source_files_properties(${file} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/${dir}")
endforeach()

#meta data for bundle
set(METADATA_DIR ${CMAKE_SOURCE_DIR}/metadata)
set(MY_APP_ICON ${CMAKE_SOURCE_DIR}/metadata/ico.icns)
set_source_files_properties(${myApp_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

#make a cmakever.h from template file and include on build
set(Template_ver metadata/cmakever.h.in )
configure_file(${Template_ver} ${CMAKE_CURRENT_BINARY_DIR}/../source/cmakever.h)



#set bundle name
set(MACOSX_BUNDLE_BUNDLE_NAME "Ekzeckt")
#set bundle version
set(MACOSX_BUNDLE_BUNDLE_VERSION "${CMAKE_PROJECT_VERSION}")
#set bundle version as string
string(CONCAT MACOSX_BUNDLE_SHORT_VERSION_STRING "v" ${CMAKE_PROJECT_VERSION_MINOR} "." ${CMAKE_PROJECT_VERSION_PATCH})
#set bundle icon
set(MACOSX_BUNDLE_ICON_FILE "ico.icns")
#configure plist file for bundle
configure_file(${METADATA_DIR}/Info.plist.in ${CMAKE_CURRENT_SOURCE_DIR}/bin/Info.plist)

##build bundle for macos
if(APPLE)
    #BUNDLE BUILD
    add_executable(Ekzeckt ${SOURCE_PROJECT_FILES} ${MY_APP_RESOURCES} ${MY_APP_ICON} ${Template_ver})
    #check for debug or release build
     if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(Ekzeckt PUBLIC -g)
    else()
        target_compile_options(Ekzeckt PUBLIC -O3)
    endif()
    #set name for bundle
    set_target_properties(Ekzeckt PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Ekzeckt")
    target_link_libraries(Ekzeckt sfml-graphics sfml-window sfml-system)
    target_link_libraries(Ekzeckt "-framework CoreFoundation")

    set_target_properties(Ekzeckt PROPERTIES MACOSX_BUNDLE TRUE)
    set_target_properties(Ekzeckt PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/bin/Info.plist)
    
endif()