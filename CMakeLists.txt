cmake_minimum_required(VERSION 3.21)
project(CLionGL)

set(CMAKE_CXX_STANDARD 20)

add_executable(CLionGL main.cpp)

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} PUBLIC external/glfw/include/GLFW)

target_link_directories(${PROJECT_NAME} PRIVATE external/glfw/src)

target_link_libraries(${PROJECT_NAME} glfw)