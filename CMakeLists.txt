cmake_minimum_required(VERSION 3.22)
project(life)

set(CMAKE_CXX_STANDARD 14)
#find_package(sdl2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
if(APPLE)
else()
    find_package(glew REQUIRED)
endif()

add_executable(life src/life.cpp src/grid.cpp)

target_link_libraries(life OpenGL::GL ${GLEW_LIBRARIES} glfw)
