cmake_minimum_required(VERSION 3.21)
project(CLionGL)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp src/GLShaderProgram.cpp src/GLTexture.cpp src/GLVertexArray.cpp headers/GLVertexArray.h src/GLBuffer.cpp headers/GLBuffer.h src/Player.cpp headers/Player.h)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        headers/
        )

configure_file(resources/shaders/solidcolor.frag resources/shaders/solidcolor.frag)
configure_file(resources/shaders/uniformcolor.frag resources/shaders/uniformcolor.frag)
configure_file(resources/shaders/solidcolor.vert resources/shaders/solidcolor.vert)
configure_file(resources/shaders/3dtransform.vert resources/shaders/3dtransform.vert)
configure_file(resources/textures/wall.jpg resources/textures/wall.jpg COPYONLY)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)

target_include_directories(${PROJECT_NAME}
        PUBLIC external/glfw/include/GLFW
        PUBLIC external/stb_image
        PUBLIC cmake-build-debug/external/glad/include/glad
        PUBLIC external/glm/glm
        )

target_link_directories(${PROJECT_NAME}
        PRIVATE external/glfw/src
        PRIVATE cmake-build-debug/external/glad
        )

target_link_libraries(${PROJECT_NAME} glfw glad)