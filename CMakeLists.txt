cmake_minimum_required(VERSION 3.0.0)

project(My_Project_MAC VERSION 0.0.3)
message("CMAKE_PROJECT_VERSION = ${CMAKE_PROJECT_VERSION}")


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RESOURCE_FILES
    MyApplication/main.cpp 
    MyApplication/Core.cpp 
    MyApplication/states/State.cpp 
    MyApplication/states/MainMenu.cpp 
    MyApplication/states/PauseMenu.cpp 
    MyApplication/states/Process.cpp 
    MyApplication/states/gfx.cpp 
    MyApplication/states/NoiceView.cpp 
    MyApplication/math/mymath.cpp 
    MyApplication/math/ProcessGenerationNoice.cpp 
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
)

set(Template_ver MyApplication/cmakever.h.in )
configure_file(${Template_ver}
${CMAKE_CURRENT_BINARY_DIR}/../MyApplication/cmakever.h
)

set(SFML_DIR  "/usr/local/lib/cmake/SFML" )
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(SFML 2.5 COMPONENTS system REQUIRED)
find_package(SFML 2.5 COMPONENTS window REQUIRED)


if(APPLE)

add_executable(Project_MAC ${RESOURCE_FILES})
set_target_properties(Project_MAC PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(Project_MAC PRIVATE ${Template_ver})
target_link_libraries(Project_MAC sfml-graphics sfml-system sfml-window)
endif()


if(WIN32)  
set(CMAKE_SYSTEM_NAME Windows)
add_executable(My_Project_WIN64 ${RESOURCE_FILES})
target_link_libraries(My_Project_WIN64 sfml-graphics sfml-system sfml-window)
set_target_properties(My_Project_WIN64 PROPERTIESCXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
endif()