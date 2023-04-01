cmake_minimum_required(VERSION 3.0.0)
project(MyApplic VERSION 0.1.1)

include(CTest)
enable_testing()

set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")
set(CMAKE_CXX_STANDARD 20)



file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS  *.cpp)
find_package(SFML COMPONENTS graphics window system)
add_executable(MyApplic MyApplication/main.cpp)
target_link_libraries(MyApplic sfml-graphics sfml-audio)







set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
