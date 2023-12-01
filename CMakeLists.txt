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
set(SOURCE_PROJECT_FILES
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
find_package(SFML 2.6.1 COMPONENTS graphics system window REQUIRED)
#for bundle
find_library(COREFOUNDATION_LIBRARY CoreFoundation)


file(GLOB_RECURSE MY_APP_RESOURCES bin/resources/*)

foreach(file IN LISTS MY_APP_RESOURCES)
    file(RELATIVE_PATH relative_path ${CMAKE_CURRENT_SOURCE_DIR}/bin/resources ${file})
    get_filename_component(dir ${relative_path} DIRECTORY)
    set_source_files_properties(${file} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/${dir}")
endforeach()

#meta data for bundle
set(METADATA_DIR ${CMAKE_SOURCE_DIR}/metadata)
set(MY_APP_ICON ${CMAKE_SOURCE_DIR}/metadata/src/ico.icns)
set_source_files_properties(${myApp_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

set(MACOSX_BUNDLE_BUNDLE_NAME "Ekzeckt")
set(MACOSX_BUNDLE_SHORT_VERSION_STRING "v" ${CMAKE_PROJECT_VERSION_MINOR} "." ${CMAKE_PROJECT_VERSION_PATCH})
string(CONCAT MACOSX_BUNDLE_SHORT_VERSION_STRING "v" ${CMAKE_PROJECT_VERSION_MINOR} "." ${CMAKE_PROJECT_VERSION_PATCH})
set(MACOSX_BUNDLE_BUNDLE_VERSION "${CMAKE_PROJECT_VERSION}")
set(MACOSX_BUNDLE_ICON_FILE "ico.icns")

configure_file(${METADATA_DIR}/Info.plist.in ${CMAKE_CURRENT_SOURCE_DIR}/bin/Info.plist)



##build
if(APPLE)
    #BIN BUILD
    add_executable(GameProto ${SOURCE_PROJECT_FILES} ${MY_APP_RESOURCES} )
    set_target_properties(GameProto PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
    target_link_libraries(GameProto sfml-graphics sfml-system sfml-window)
    target_include_directories(GameProto PRIVATE ${Template_ver}) #include generate config file
    target_include_directories(GameProto PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}) #include resource files
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}) 



    #BUNDLE BUILD
    add_executable(Ekzeckt ${SOURCE_PROJECT_FILES} ${MY_APP_RESOURCES} ${MY_APP_ICON})

    #include CoreFoundation for some shet idk for what, but without this line i cant get path to resources in bundle
    #LMAO
    target_link_libraries(Ekzeckt "-framework CoreFoundation")
    
    #set name for bundle
    target_compile_options(Ekzeckt PUBLIC -O3)
    set_target_properties(Ekzeckt PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "Ekzeckt")
    set_target_properties(Ekzeckt PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
    target_link_libraries(Ekzeckt sfml-graphics sfml-window sfml-system)

    
    target_sources(Ekzeckt PRIVATE ${MY_APP_RESOURCES})
    set_target_properties(Ekzeckt PROPERTIES MACOSX_BUNDLE TRUE)
    set_target_properties(Ekzeckt PROPERTIES RESOURCE "${MY_APP_ICON}")
    set_target_properties(Ekzeckt PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/bin/Info.plist)

    
    
    
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BUNDLE_OUTPUT_DIRECTORY}) 
    
endif()
    
    
    
    