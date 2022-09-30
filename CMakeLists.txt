cmake_minimum_required(VERSION 3.22)
project(life)

set(CMAKE_CXX_STANDARD 20)
#find_package(sdl2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(glm REQUIRED)
find_package(fmt REQUIRED)
if(APPLE)
else()
    find_package(GLEW REQUIRED)
endif()

add_executable(life src/life.cpp src/grid.cpp src/shader.cpp src/camera.cpp)

target_link_libraries(life OpenGL::GL ${GLEW_LIBRARIES} glfw GLEW::GLEW fmt::fmt)
