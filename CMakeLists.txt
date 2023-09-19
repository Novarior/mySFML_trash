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
    source/main.cpp 
    source/Core.cpp 
    source/states/gfx.cpp
    source/math/mymath.cpp
    source/math/simplex.cpp
    source/math/LSystem.cpp
    source/source/mypars/parsJSON.cpp
    source/math/ProcessGenerationNoice.cpp
    #include states
    source/states/State.cpp
    source/states/Process.cpp
    source/states/MainMenu.cpp
    source/states/settings.cpp
    source/states/NoiceView.cpp
    source/states/PauseMenu.cpp
    #gui includes
    source/GUI/components/button.cpp
    source/GUI/components/minimap.cpp
    source/GUI/components/textbox.cpp
    source/GUI/components/selector.cpp
    source/GUI/components/ProgressBar.cpp
    source/GUI/components/dropDownList.cpp
    source/GUI/components/staticSelector.cpp
    source/GUI/components/textureSelector.cpp
    #entitys includes
    source/entitys/entity.cpp 
    source/entitys/player.cpp 
    source/entitys/Enemys/Slime.cpp 
    #AI includes
    source/entitys/AI/AIFollow.cpp 
    source/entitys/AI/AIComponent.cpp 
    source/entitys/AI/AIAttack.cpp
    #properties includes
    source/entitys/properties/hitbox.cpp 
    source/entitys/properties/movement.cpp 
    source/entitys/properties/attributes.cpp
    #map includes
    source/Content/Map/block.cpp 
    source/Content/Map/TileMap.cpp
    #items includes
    source/Content/ItemsStuff/Inventory.cpp
    #ect includes
    source/Content/rotationCircle.cpp 
)

#set outputs directorry
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#make a cmakever.h from template file and include on build
set(Template_ver source/cmakever.h.in )
configure_file(${Template_ver} ${CMAKE_CURRENT_BINARY_DIR}/../source/cmakever.h)

#include SFML library on project
set(SFML_DIR  "/usr/local/lib/cmake/SFML" )
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(SFML 2.5 COMPONENTS system REQUIRED)
find_package(SFML 2.5 COMPONENTS window REQUIRED)

set(CMAKE_TOOLCHAIN_FILE "build/toolchain.cmake")


##build
if(APPLE)
add_executable(GameProto ${RESOURCE_FILES})

set_target_properties(GameProto PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
target_link_libraries(GameProto sfml-graphics sfml-system sfml-window)
target_include_directories(GameProto PRIVATE ${Template_ver}) #include generate config file
target_include_directories(GameProto PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) #include resource files

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 
message("GameProto" ${CMAKE_BINARY_DIR}/bin)
endif()

if(WIN64)
    # Путь к компилятору i686-w64-mingw32-g++
    set(CMAKE_C_COMPILER "/opt/local/bin/i686-w64-mingw32-gcc")
    set(CMAKE_CXX_COMPILER "/opt/local/bin/i686-w64-mingw32-g++")
    # Путь к компилятору x86_64-w64-mingw32-g++
    set(CMAKE_C_COMPILER "/opt/local/bin/x86_64-w64-mingw32-gcc")
    set(CMAKE_CXX_COMPILER "/opt/local/bin/x86_64-w64-mingw32-g++")

    # Смена системы на Windows
    set(CMAKE_SYSTEM_NAME Windows)

    try_compile(COMPILE_RESULT ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp)
    
    add_executable(GameProto_Windows ${RESOURCE_FILES})

    set_target_properties(GameProto_Windows PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
    target_link_libraries(GameProto_Windows sfml-graphics sfml-system sfml-window)


    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    message("GameProto_Windows" ${CMAKE_BINARY_DIR}/bin)
endif()
###