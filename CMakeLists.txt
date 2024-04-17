cmake_minimum_required(VERSION 3.20)

project(fedulov-p-s-23-02)

set(CMAKE_CXX_STANDARD 20)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG bin.dbg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE bin.rel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO bin.relwithdbg)

option(BUILD_WITH_SAMPLES "Build prj.cw sample targets" off)

add_subdirectory(prj.codeforces)

add_subdirectory(prj.lab)

add_subdirectory(prj.test)

if(BUILD_WITH_SAMPLES)
  add_subdirectory(prj.cw)
endif()
