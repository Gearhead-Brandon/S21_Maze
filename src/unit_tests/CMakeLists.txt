cmake_minimum_required(VERSION 3.0)

project(BrickGame LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER "/usr/bin/g++-11")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fprofile-arcs -ftest-coverage -Wall -Werror -Wextra") 

file(GLOB SOURCE_FILES
    "*.cpp"
    "**/*.cpp"
)

file (GLOB_RECURSE COMMON_FILES
    "../App/Common/*.cpp"
    "../App/Model/FileReader/*.cpp"
)

file(GLOB_RECURSE MAZE_FILES
    "../App/Model/Maze/*.cpp"
)

file(GLOB_RECURSE CAVE_FILES
    "../App/Model/Cave/*.cpp"
)

#Create a library target
add_library(Common STATIC ${COMMON_FILES})
add_library(Maze STATIC ${MAZE_FILES})
add_library(Cave STATIC ${CAVE_FILES})

# Create an executable target
add_executable(Tests ${SOURCE_FILES})

# Add necessary libraries or dependencies
target_link_libraries(
    Tests
    Maze
    Cave
    Common
    -lgtest
    -lm
)

set_target_properties(
    Tests
    PROPERTIES
    LINK_FLAGS "--coverage"
    ENABLE_TESTING TRUE
)