cmake_minimum_required(VERSION 3.0)

project(BrickGame LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER "/usr/bin/g++-11")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -Wextra") 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fprofile-arcs -ftest-coverage") 

# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)
# find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)

file(GLOB MAIN
    "*.cpp"
)

file(GLOB_RECURSE MAZE_FILES
    "../App/Model/Maze/*.cpp"
    "../App/Common/*.cpp"
)

#Create a library target

add_library(Maze STATIC ${MAZE_FILES})

# Create an executable target
add_executable(Tests ${MAIN})

# Add necessary libraries or dependencies
target_link_libraries(
    Tests
    Maze
    -lgtest
    -lm
)

set_target_properties(
    Tests
    PROPERTIES
    #COMPILE_FLAGS "-fprofile-arcs -ftest-coverage"
    LINK_FLAGS "--coverage"
    ENABLE_TESTING TRUE
)