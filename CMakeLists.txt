#set minimun cmake version for build 
cmake_minimum_required(VERSION 3.5.0)
project(TRYSQUARE VERSION 0.0.3)
message("CMAKE_PROJECT_VERSION = ${CMAKE_PROJECT_VERSION}")

#set miniimum c++ standart 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#include all files for build project
set(RESOURCE_FILES
    MyApplication/main.cpp 
    MyApplication/Core.cpp 
    MyApplication/math/noice.hpp
    MyApplication/math/mymath.cpp
    MyApplication/math/ProcessGenerationNoice.cpp
    MyApplication/states/ConstFoldersFlow.h
    MyApplication/states/gfx.cpp
    MyApplication/states/MainMenu.cpp
    MyApplication/states/NoiceView.cpp
    MyApplication/states/PauseMenu.cpp
    MyApplication/states/Process.cpp
    MyApplication/states/State.cpp
    MyApplication/GUI/GUISYS.cpp 
    MyApplication/GUI/tabMenu.cpp 
    MyApplication/entitys/entity.cpp 
    MyApplication/entitys/player.cpp 
    MyApplication/entitys/Enemys/test.cpp 
    MyApplication/entitys/AI/AIFollow.cpp 
    MyApplication/entitys/AI/AIComponent.cpp 
    MyApplication/entitys/properties/hitbox.cpp 
    MyApplication/entitys/properties/movement.cpp 
    MyApplication/Content/rotationCircle.cpp 
    MyApplication/Content/Map/block.cpp 
    MyApplication/Content/Map/TileMap.cpp
    MyApplication/Content/ItemsStuff/Coins.cpp
    MyApplication/Content/ItemsStuff/Inventory.cpp
    MyApplication/Content/ItemsStuff/Item.cpp
)

#set outputs directorry
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


#make a cmakever.h from template file and include on build
set(Template_ver MyApplication/cmakever.h.in )
configure_file(${Template_ver} ${CMAKE_CURRENT_BINARY_DIR}/../MyApplication/cmakever.h)


#include SFML library on priject
set(SFML_DIR  "/usr/local/lib/cmake/SFML" )
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(SFML 2.5 COMPONENTS system REQUIRED)
find_package(SFML 2.5 COMPONENTS window REQUIRED)

##build
if(APPLE)
add_executable(GameProto ${RESOURCE_FILES})

set_target_properties(GameProto PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_link_libraries(GameProto sfml-graphics sfml-system sfml-window)
target_include_directories(GameProto PRIVATE ${Template_ver}) #include generate config file
target_include_directories(GameProto PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) #include resource files


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/debug) 
message("GameProto" ${CMAKE_BINARY_DIR}/debug)
endif()


if(WIN32)  
set(CMAKE_SYSTEM_NAME Windows)
add_executable(GameProto ${RESOURCE_FILES})
target_link_libraries(GameProto sfml-graphics sfml-system sfml-window)
set_target_properties(GameProto PROPERTIESCXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
endif()


###