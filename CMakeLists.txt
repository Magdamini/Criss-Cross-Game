cmake_minimum_required(VERSION 3.22)
project(project)

set(CMAKE_CXX_STANDARD 20)

add_executable(project main.cpp board.h board.cpp ClickDetector.h ClickDetector.cpp Button.h Button.cpp Button.cpp Button.h DisplayFunctions.h DisplayFunctions.h DisplayFunctions.cpp)

## windows
#set(SFML_STATIC_LIBRARIES TRUE)
#set(SFML_DIR C:/SFML/lib/cmake/SFML)
#find_package(SFML 2.5 COMPONENTS system window graphics audio network main REQUIRED)
#include_directories(C:/SFML/include)
#target_link_libraries(project sfml-system sfml-window sfml-graphics sfml-audio sfml-main)

# linux
set(SFML_DIR /usr/lib/x86_64-linux-gnu/cmake/SFML)
#set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML 2.5 COMPONENTS system window graphics audio network REQUIRED)
include_directories(/usr/include)
target_link_libraries(project sfml-system sfml-window sfml-graphics sfml-audio)
