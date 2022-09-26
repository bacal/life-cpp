cmake_minimum_required(VERSION 3.22)
project(life)

set(CMAKE_CXX_STANDARD 14)
find_package(sdl2 REQUIRED)


add_executable(life main.cpp)

target_link_libraries(life SDL2::SDL2)
