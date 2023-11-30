#set minimun cmake version for build 
cmake_minimum_required(VERSION 3.5.0)
project(SFMLGAME VERSION 0.0.5)

#set miniimum c++ standart 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set build type
set(CMAKE_BUILD_TYPE Debug)

message("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message("CMAKE_PROJECT_VERSION = ${CMAKE_PROJECT_VERSION}")

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
    source/states/editModes/NoiceViewer.cpp
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
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Debug)
set(CMAKE_BUNDLE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Bundle)

#make a cmakever.h from template file and include on build
set(Template_ver source/cmakever.h.in )
configure_file(${Template_ver} ${CMAKE_CURRENT_BINARY_DIR}/../source/cmakever.h)

#include SFML library on project
find_package(SFML 2.6.1 COMPONENTS graphics REQUIRED)
find_package(SFML 2.6.1 COMPONENTS system REQUIRED)
find_package(SFML 2.6.1 COMPONENTS window REQUIRED)

#for bundle
find_library(COREFOUNDATION_LIBRARY CoreFoundation)


##build
if(APPLE)
    #if debug build
        add_executable(GameProto ${RESOURCE_FILES})

        set_target_properties(GameProto PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
        target_link_libraries(GameProto sfml-graphics sfml-system sfml-window)
        target_include_directories(GameProto PRIVATE ${Template_ver}) #include generate config file
        target_include_directories(GameProto PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) #include resource files

        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}) 


        #else if release build

        #include CoreFoundation for some shet idk for what, but without this line i cant get path to resources in bundle
        #LMAO
        target_link_libraries(Ekzeckt "-framework CoreFoundation")

        #set name for bundle
        target_compile_options(Ekzeckt PUBLIC -O3)
        set_target_properties(Ekzeckt PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Ekzeckt")
        set_target_properties(Ekzeckt PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
        target_link_libraries(Ekzeckt sfml-graphics sfml-window sfml-system)
    
        set_target_properties(Ekzeckt PROPERTIES MACOSX_BUNDLE TRUE)
        set_target_properties(Ekzeckt PROPERTIES MACOSX_BUNDLE_BUNDLE_VERSION ${CMAKE_BUILD_TYPE})
        set_target_properties(Ekzeckt PROPERTIES MACOSX_BUNDLE_SHORT_VERSION_STRING ${CMAKE_BUILD_TYPE})
        set_target_properties(Ekzeckt PROPERTIES MACOSX_BUNDLE_LONG_VERSION_STRING ${CMAKE_BUILD_TYPE})
        set_target_properties(Ekzeckt PROPERTIES MACOSX_BUNDLE_ICON_FILE "ico.png")
        set_target_properties(Ekzeckt PROPERTIES RESOURCE "${myApp_ICON}")
        set_target_properties(Ekzeckt PROPERTIES RESOURCE "${myApp_FONT}")
        
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 


    endif()
endif()


