cmake_minimum_required(VERSION 3.10)

project(2DEngine VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)
add_executable(
    2DEngine src/main.cpp
    )
target_link_libraries(2DEngine SDL2::SDL2 SDL2::SDL2main)