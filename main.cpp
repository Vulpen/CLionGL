#include "GLShaderProgram.h"
#include "GLTexture.h"
#include "GLVertexArray.h"
#include "GLBuffer.h"
#include "Player.h"
#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include <glm.hpp>
#include <ext.hpp>

GLShaderProgram solidColorShader;
GLTexture brickTexture;
GLVertexArray vertArray;
GLBuffer vertBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
GLBuffer indexBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

Player *mainPlayer;

void glfw_resize_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    GLShaderProgram::ProjectionMatrix = glm::perspective(glm::radians(45.0f), width / (float)height, 1.0f, 3.0f);
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

    window = glfwCreateWindow(300, 300, "Welcome to CLion!", NULL, NULL);
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
    glViewport(0, 0, 300, 300);

    glfwSetFramebufferSizeCallback(window, glfw_resize_callback);

    //glfwSwapInterval(1);

    // Vertices defined in normalized device coordinates!
    // Probably should switch to GLFloats.
    float vertices[] = {
            -0.25 + -0.25, -0.25, 0,
            0 + -0.25, 0.25, 0,
            0.25 + -0.25, -0.25, 0
    };
    float vertices2[] = {
            -0.25 + 0.25, -0.25, 0,
            0 + 0.25, 0.25, 0,
            0.25 + 0.25, -0.25, 0
    };
    unsigned int indices[] = {
            0, 1, 2,
    };

    mainPlayer = new Player();

    vertArray.Generate();
    vertBuffer.Generate((GLvoid*)vertices, 9 * sizeof(GLfloat));
    indexBuffer.Generate((GLvoid*)indices, 3 * sizeof(GLuint));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    vertBuffer.unbind();
    indexBuffer.unbind();

    // VAO 0
    unsigned int VAO1, VAO2, VBO1, VBO2, EBO;
    glGenVertexArrays(1, &VAO1);
    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO1);
    glGenBuffers(1, &VBO2);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glDisable(GL_CULL_FACE);

    brickTexture.loadTexture("resources/textures/wall.jpg");
    solidColorShader.loadAndCompileShaders("resources/shaders/3dtransform.vert", "resources/shaders/solidcolor.frag");
    GLfloat greenValue = 0.0f;

    glm::mat4x4 model = glm::mat4(1.0f);
    glm::mat4x4 view = glm::mat4x4(1.0f);
    glm::mat4x4 projection = glm::mat4x4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    GLShaderProgram::ViewMatrix = glm::translate(glm::mat4x4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    // TODO: change to use screen height and width
    projection = glm::perspective(glm::radians(45.0f), 300.0f / 300.0f, 0.1f, 100.0f);
    GLShaderProgram::ProjectionMatrix = glm::perspective(glm::radians(45.0f), 300.0f / 300.0f, 1.0f, 3.0f);
    solidColorShader.use();
    solidColorShader.setUniform("model", model);
    solidColorShader.setUniform("view", view);
    solidColorShader.setUniform("projection", projection);

    std::cout << glGetError() << std::endl;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        greenValue += 0.001;
        if (greenValue > 1.0f) {
            greenValue = 0.0f;
        }

//        brickTexture.use();
//        solidColorShader.use();
//        solidColorShader.setUniform("uColor", greenValue);
//        //glBindVertexArray(VAO1);
//        vertArray.use();
//        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
//        glBindVertexArray(VAO2);
//        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        mainPlayer->Draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();

    // Exit program
    exit(EXIT_SUCCESS);
}