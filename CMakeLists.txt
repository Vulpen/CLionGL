cmake_minimum_required(VERSION 3.21)
project(CLionGL)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        headers/
        )

add_subdirectory(external/glfw)
add_subdirectory(external/glad)

target_include_directories(${PROJECT_NAME}
        PUBLIC external/glfw/include/GLFW
        PUBLIC cmake-build-debug/external/glad/include/glad
        )

target_link_directories(${PROJECT_NAME}
        PRIVATE external/glfw/src
        PRIVATE cmake-build-debug/external/glad
        )

target_link_libraries(${PROJECT_NAME} glfw glad)