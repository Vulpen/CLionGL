#include "Player.h"

Player::Player() :
        mVertexBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW),
        mIndexBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW),
        scale(0.33),
        location(0.0, 0.0) {

    GLfloat vertices[] = {
            -0.25, -0.25, 0,
            0, 0.75, 0,
            0, 0, 0,
            0.25, -0.25, 0
    };

    GLuint indices[] = {
            0, 1, 2,
            2, 1, 3
    };

    mVertexArray.Generate();
    mVertexBuffer.Generate((GLvoid *) vertices, 12 * sizeof(GLfloat));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    mIndexBuffer.Generate((GLvoid *) indices, 6 * sizeof(GLfloat));
    glBindVertexArray(0);
    mVertexBuffer.unbind();
    mIndexBuffer.unbind();

    mShaderProgram.loadAndCompileShaders("resources/shaders/3dtransform.vert", "resources/shaders/solidcolor.frag");
}

void Player::Draw() {
    mShaderProgram.use();
    glm::mat4 model = glm::translate(
            glm::mat4(1.0f),
            glm::vec3(location.x, location.y, 0)
            )
                    * glm::scale(glm::mat4(1.0f), glm::vec3(scale));
    mShaderProgram.setUniform("model", model);
    mShaderProgram.setUniform("view", GLShaderProgram::ViewMatrix);
    mShaderProgram.setUniform("projection", GLShaderProgram::ProjectionMatrix);
    mShaderProgram.setUniform("uColor", 0.5f);
    mVertexArray.use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Player::HandleInput(int x, int y) {
    location.y += y * 0.03;
    location.x += x * 0.03;
}

void Player::Update() {

}
