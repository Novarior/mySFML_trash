#set minimun cmake version for build 
cmake_minimum_required(VERSION 3.5.0)
project(SFMLGAME VERSION 0.0.5)
message("CMAKE_PROJECT_VERSION = ${CMAKE_PROJECT_VERSION}")

#set miniimum c++ standart 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#include all files for build project
set(RESOURCE_FILES
#core includes
    MyApplication/main.cpp 
    MyApplication/Core.cpp 
    MyApplication/states/gfx.cpp
    MyApplication/math/mymath.cpp
    MyApplication/source/mypars/parsJSON.cpp
    MyApplication/math/ProcessGenerationNoice.cpp
    #include states
    MyApplication/states/State.cpp
    MyApplication/states/Process.cpp
    MyApplication/states/MainMenu.cpp
    MyApplication/states/settings.cpp
    MyApplication/states/NoiceView.cpp
    MyApplication/states/PauseMenu.cpp
    #gui includes
    MyApplication/GUI/components/button.cpp
    MyApplication/GUI/components/minimap.cpp
    MyApplication/GUI/components/textbox.cpp
    MyApplication/GUI/components/selector.cpp
    MyApplication/GUI/components/ProgressBar.cpp
    MyApplication/GUI/components/dropDownList.cpp
    MyApplication/GUI/components/staticSelector.cpp
    MyApplication/GUI/components/textureSelector.cpp
    #entitys includes
    MyApplication/entitys/entity.cpp 
    MyApplication/entitys/player.cpp 
    MyApplication/entitys/Enemys/Slime.cpp 
    #AI includes
    MyApplication/entitys/AI/AIFollow.cpp 
    MyApplication/entitys/AI/AIComponent.cpp 
    #properties includes
    MyApplication/entitys/properties/hitbox.cpp 
    MyApplication/entitys/properties/movement.cpp 
    MyApplication/entitys/properties/attributes.cpp
    #map includes
    MyApplication/Content/Map/block.cpp 
    MyApplication/Content/Map/TileMap.cpp
    #items includes
    MyApplication/Content/ItemsStuff/Item.hpp
    MyApplication/Content/ItemsStuff/Coins.cpp
    MyApplication/Content/ItemsStuff/Inventory.cpp
    #ect includes
    MyApplication/Content/rotationCircle.cpp 
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

set_target_properties(GameProto PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_link_libraries(GameProto sfml-graphics sfml-system sfml-window)
target_include_directories(GameProto PRIVATE ${Template_ver}) #include generate config file
target_include_directories(GameProto PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) #include resource files

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/debug) 
message("GameProto" ${CMAKE_BINARY_DIR}/debug)
endif()


###