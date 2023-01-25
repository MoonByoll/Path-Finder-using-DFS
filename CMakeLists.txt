cmake_minimum_required(VERSION 3.23)
project(sfmlTest)

set(CMAKE_CXX_STANDARD 17)

add_executable(newMazeStar main.cpp maze.cpp maze.h MyArrayStack.cpp MyArrayStack.h Random.cpp Random.h)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(newMazeStar sfml-system sfml-window sfml-graphics sfml-audio)