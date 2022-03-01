cmake_minimum_required(VERSION 3.21)
project(CLionGL)

set(CMAKE_CXX_STANDARD 20)

add_executable(CLionGL main.cpp)

add_subdirectory(external/glfw)
