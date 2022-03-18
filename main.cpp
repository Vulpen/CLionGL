#include "GLShaderProgram.h"
#include "Player.h"
#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include <glm.hpp>
#include <ext.hpp>

Player *mainPlayer;

void glfw_resize_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    //GLShaderProgram::ProjectionMatrix = glm::perspective(glm::radians(45.0f), width / (float)height, 1.0f, 3.0f);
    GLShaderProgram::ProjectionMatrix = glm::ortho(
            width * -0.5f,
            width * 0.5f,
            height * -0.5f,
            height * 0.5f,
            0.1f,
            100.0f);
    GLShaderProgram::ScreenWidth = width;
    GLShaderProgram::ScreenHeight = height;
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    int xIn = 0, yIn = 0;

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        yIn = 1;
    } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        yIn = -1;
    }

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        xIn = 1;
    } else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        xIn = -1;
    }

    if(mainPlayer && (yIn != 0 || xIn != 0)) {
        mainPlayer->HandleInput(xIn, yIn);
    }
}

/* program entry */
int main(int argc, char *argv[]) {

    GLShaderProgram::ViewMatrix = glm::mat4(1.0f);
    GLShaderProgram::ProjectionMatrix = glm::mat4(1.0f);

    GLFWwindow *window;
    int width, height;

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_DEPTH_BITS, 16);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); For MacOS!

    window = glfwCreateWindow(INIT_SCREEN_WIDTH, INIT_SCREEN_HEIGHT, "Welcome to CLion!", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD :'( " << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glViewport(0, 0, INIT_SCREEN_WIDTH, INIT_SCREEN_HEIGHT);

    glfwSetFramebufferSizeCallback(window, glfw_resize_callback);

    mainPlayer = new Player();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glDisable(GL_CULL_FACE);

    GLShaderProgram::ViewMatrix = glm::translate(glm::mat4x4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    //GLShaderProgram::ProjectionMatrix = glm::perspective(glm::radians(45.0f), 300.0f / 300.0f, 1.0f, 3.0f);
    GLShaderProgram::ProjectionMatrix = glm::ortho(
            -INIT_SCREEN_WIDTH / 2.0f, INIT_SCREEN_WIDTH / 2.0f,
            -INIT_SCREEN_HEIGHT / 2.0f, INIT_SCREEN_HEIGHT/ 2.0f,
            0.1f, 100.0f);
    std::cout << glGetError() << std::endl;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        mainPlayer->Update();


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        mainPlayer->Draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    // Exit program
    exit(EXIT_SUCCESS);
}