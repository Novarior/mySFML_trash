# Установка минимальной версии CMake
cmake_minimum_required(VERSION 3.10.0)
project(Ekzeckt VERSION 0.0.10)

# Установка минимальной версии C++ стандарта
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Установка типа сборки
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Debug)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Bundle)
endif()

# Включение всех файлов проекта
file(GLOB_RECURSE SOURCE_PROJECT_FILES source/*.cpp)

# Поиск библиотеки SFML
find_package(SFML 3.0.0 REQUIRED COMPONENTS Graphics Audio Network System)
message("SFML was found = ${SFML_FOUND}")

# Поиск библиотеки nlohmann_json
find_package(nlohmann_json 3.11.3 REQUIRED)
if(NOT nlohmann_json_FOUND)
    message(FATAL_ERROR "nlohmann_json was not found")
else()
    message(STATUS "nlohmann_json was found")
endif()

# Функция для копирования фреймворков в папку бандла
function(copy_to_bundle target)
    get_filename_component(framework_name ${target} NAME)
    set(destination "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Ekzeckt.app/Contents/Frameworks/${framework_name}")
    add_custom_command(
        TARGET Ekzeckt POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${target} ${destination}
        COMMENT "Copying framework ${framework_name} to bundle"
    )
endfunction()

# Поиск файлов в папке ресурсов
file(GLOB_RECURSE MY_APP_RESOURCES source/res/*)
foreach(file IN LISTS MY_APP_RESOURCES)
    file(RELATIVE_PATH relative_path ${CMAKE_CURRENT_SOURCE_DIR}/source/res ${file})
    get_filename_component(dir ${relative_path} DIRECTORY)
    set_source_files_properties(${file} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources/${dir}")
endforeach()

# Конфигурация иконки приложения
set(METADATA_DIR ${CMAKE_SOURCE_DIR}/metadata)
set(MY_APP_ICON ${CMAKE_SOURCE_DIR}/metadata/ico.png)
set_source_files_properties(${MY_APP_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

# Генерация cmakever.h
set(Template_ver metadata/cmakever.h.in)
configure_file(${Template_ver} ${CMAKE_CURRENT_BINARY_DIR}/../source/cmakever.h)

if(APPLE)
    # Конфигурация plist файла для бандла
    set(DATA_BUNDLE_BUNDLE_NAME "Ekzeckt")
    set(DATA_BUNDLE_GUI_IDENTIFIER "com.ekzeckt")
    set(DATA_BUNDLE_COPYRIGHT "© 2023 GitHub: Novarior")
    set(DATA_BUNDLE_INFO_STRING "Ekzeckt")
    set(DATA_BUNDLE_BUNDLE_VERSION "${CMAKE_PROJECT_VERSION}")
    string(CONCAT DATA_BUNDLE_SHORT_VERSION_STRING "v" ${CMAKE_PROJECT_VERSION_MINOR} "." ${CMAKE_PROJECT_VERSION_PATCH})

    set(DATA_BUNDLE_ICON_NAME "ico.png")
    set(DATA_BUNDLE_ICON_FILE ${CMAKE_SOURCE_DIR}/metadata/ico.png)

    configure_file(${METADATA_DIR}/Info.plist.in ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Info.plist)

    # Сборка приложения
    add_executable(Ekzeckt MACOSX_BUNDLE ${SOURCE_PROJECT_FILES} ${MY_APP_RESOURCES} ${Template_ver} ${DATA_BUNDLE_ICON_FILE})
    
    # Настройка флагов компиляции в зависимости от режима сборки
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(Ekzeckt PUBLIC -g)
    else()
        target_compile_options(Ekzeckt PUBLIC -O3)
    endif()

    # Линковка с библиотеками
    target_link_libraries(Ekzeckt PRIVATE 
        SFML::Graphics
        SFML::Audio
        SFML::Network
        SFML::System
        nlohmann_json::nlohmann_json
        "-framework CoreFoundation"
        "-framework CoreServices"
         "-framework IOKit"
    )

    # Установка rpath
    set_target_properties(Ekzeckt PROPERTIES
        INSTALL_RPATH "@executable_path/../Frameworks"
        BUILD_WITH_INSTALL_RPATH TRUE
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Info.plist
    )

    # Копирование библиотек SFML в бандл
    foreach(library IN LISTS SFML_LIBRARY_DIRS)
        copy_to_bundle(${library})
    endforeach()
endif()

# Указываем путь к файлам, которые будут установлены
install(TARGETS Ekzeckt DESTINATION bin)

# Указываем дополнительные файлы (например, документацию)
install(FILES README.md DESTINATION share/doc/MyApp)

# Настройка CPack
set(CPACK_PACKAGE_NAME "EKZECKT")                # Имя пакета
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}") # Версия пакета
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "My Application Installer")
set(CPACK_PACKAGE_VENDOR "Novarior FLow")
set(CPACK_PACKAGE_CONTACT "Xle6yIIIeK1337@gmail.com")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE") # Файл лицензии
set(CPACK_PACKAGE_INSTALL_DIRECTORY "MyAppInstallDir")         # Директория установки
set(CPACK_PACKAGE_EXECUTABLES "EKZECKT" "My Application")
set(CPACK_NSIS_DISPLAY_NAME "My Application Installer")

# Указываем генераторы пакетов
set(CPACK_GENERATOR "ZIP;TGZ;NSIS;DragNDrop") # Генерация пакетов в формате ZIP и TAR.GZ

# Подключаем CPack
include(CPack)