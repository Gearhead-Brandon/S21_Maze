cmake_minimum_required(VERSION 3.0)

project(Maze LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER "/usr/bin/g++-11")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -Wextra") 

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)

file(GLOB MAIN
    "./main.cpp"
)

file(GLOB_RECURSE SOURCE_FILES
    "./App/*.h"
    "./App/*.cpp"
)

# Create an executable target
add_executable(Maze ${MAIN} ${SOURCE_FILES})

# Add necessary libraries or dependencies
target_link_libraries(
    Maze
    Qt6::Core 
    Qt6::Gui 
    Qt6::Widgets
    -lm
)