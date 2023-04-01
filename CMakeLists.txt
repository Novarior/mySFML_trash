cmake_minimum_required(VERSION 3.0.0)

project(MyFirstApp VERSION 0.1.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BINARY_DIR MyFirstApp/result)

set(RES_FILES
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

if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES arm64)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa")

endif()
if(WIN32)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
endif()

set(SFML_DIR  "/usr/local/lib/cmake/SFML" )
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(SFML 2.5 COMPONENTS system REQUIRED)
find_package(SFML 2.5 COMPONENTS window REQUIRED)

add_executable(MyApplic ${RES_FILES})
target_link_libraries(MyApplic sfml-graphics sfml-system sfml-window)