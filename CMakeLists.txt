cmake_minimum_required(VERSION 3.5.0)

project(TRYSQUARE VERSION 0.0.3)
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

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
message("CMAKE_ARCHIVE_OUTPUT_DIRECTORY = ${CMAKE_BINARY_DIR}")




set(SFML_DIR  "/usr/local/lib/cmake/SFML" )
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(SFML 2.5 COMPONENTS system REQUIRED)
find_package(SFML 2.5 COMPONENTS window REQUIRED)


if(APPLE)

add_executable(Binary-system ${RESOURCE_FILES})
set_target_properties(Binary-system PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
target_include_directories(Binary-system PRIVATE ${Template_ver})
target_link_libraries(Binary-system sfml-graphics sfml-system sfml-window)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/debug) 
endif()

if(WIN32)  
set(CMAKE_SYSTEM_NAME Windows)
add_executable(Binary-system ${RESOURCE_FILES})
target_link_libraries(Binary-system sfml-graphics sfml-system sfml-window)
set_target_properties(Binary-system PROPERTIESCXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
endif()

set_target_properties(Binary-system
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/2"
)

message("RUNTIME_OUTPUT_DIRECTORY = ${CMAKE_SOURCE_DIR}")