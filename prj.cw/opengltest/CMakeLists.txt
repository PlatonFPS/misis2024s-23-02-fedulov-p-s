#cmake_minimum_required(VERSION 3.20)

#project("OpenGLTest")

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(glfw)

add_subdirectory(glad)

add_subdirectory(shader)

add_executable(WindowTest WindowTest.cpp)

target_link_libraries(WindowTest PUBLIC glfw glad shader)