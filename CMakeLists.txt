cmake_minimum_required(VERSION 3.22)
project(life)

set(CMAKE_CXX_STANDARD 20)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(life src/main.cpp)

target_link_libraries(life ${SDL2_LIBRARIES})
