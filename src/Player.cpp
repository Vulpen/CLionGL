#include "Player.h"

Player::Player() :
        mVertexBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW),
        mIndexBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW),
        mTransform() {
    mTransform.scale = glm::vec2 (40,40);

    GLfloat vertices[] = {
            -0.25, 0.25, 0,
            0.75, 0, 0,
            0, 0, 0,
            -0.25, -0.25, 0
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
    glm::mat4x4 model = mTransform.GenerateModelTransform();
    mShaderProgram.setUniform("model", model);
    mShaderProgram.setUniform("view", GLShaderProgram::ViewMatrix);
    mShaderProgram.setUniform("projection", GLShaderProgram::ProjectionMatrix);
    mShaderProgram.setUniform("uColor", 0.5f);
    mVertexArray.use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glm::vec3 clipLocation = GLShaderProgram::WorldToClip(
            glm::vec3(mTransform.location.x, mTransform.location.y, 0)
            );

    // Handle Ghost Ship ---
    glm::vec2 originalLocation = mTransform.location;
    glm::vec2 offsetLocation = originalLocation;
    if(clipLocation.x < -0.9f) {
        // Draw another ship offset by negative screen width
        offsetLocation.x = originalLocation.x - GLShaderProgram::ScreenWidth;
    } else if (clipLocation.x > 0.9f) {
        offsetLocation.x = originalLocation.x + GLShaderProgram::ScreenWidth;
    }

    if(clipLocation.y < -0.9f) {
        // Draw another ship offset by negative screen width
        offsetLocation.y = originalLocation.y - GLShaderProgram::ScreenHeight;
    } else if (clipLocation.y > 0.9f) {
        offsetLocation.y = originalLocation.y + GLShaderProgram::ScreenHeight;
    }

    if(offsetLocation != originalLocation) {
        mShaderProgram.use();
        mTransform.location = offsetLocation;
        glm::mat4x4 model = mTransform.GenerateModelTransform();
        mShaderProgram.setUniform("model", model);
        mShaderProgram.setUniform("view", GLShaderProgram::ViewMatrix);
        mShaderProgram.setUniform("projection", GLShaderProgram::ProjectionMatrix);
        mShaderProgram.setUniform("uColor", 0.5f);
        mVertexArray.use();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        mTransform.location = originalLocation;
    }
    std::cout << clipLocation.x << std::endl;
}

void Player::HandleInput(int x, int y) {
    mTransform.SetRotation(mTransform.GetRotation() - x * 0.01);
    glm::vec2 fwd = mTransform.forward();
    if(y != 0) {
        mTransform.location += fwd * (0.6f * y);
    }
}

void Player::Update() {
    glm::vec3 clipLocation = GLShaderProgram::WorldToClip(
            glm::vec3(mTransform.location.x, mTransform.location.y, 0)
    );

    if(clipLocation.x < -1.05f) {
        // Draw another ship offset by negative screen width
        mTransform.location.x -= GLShaderProgram::ScreenWidth;
    } else if (clipLocation.x > 1.05f) {
        mTransform.location.x += GLShaderProgram::ScreenWidth;
    }

    if(clipLocation.y < -1.05f) {
        // Draw another ship offset by negative screen width
        mTransform.location.y -= GLShaderProgram::ScreenHeight;
    } else if (clipLocation.y > 1.05f) {
        mTransform.location.y += GLShaderProgram::ScreenHeight;
    }
}
