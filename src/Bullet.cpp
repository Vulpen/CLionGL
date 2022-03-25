//
// Created by Tom on 3/20/2022.
//

#include "Bullet.h"

Bullet::Bullet():
mRadius(5.0f),
mShader(),
mTransform()
{
    mShader.loadAndCompileShaders("resources/shaders/2dcircle.vert", "resources/shaders/2dcircle.frag");
}

void Bullet::Init(glm::vec2 location, float rotationRads) {
    mTransform.location = location;
    mTransform.SetRotation(rotationRads);
}

void Bullet::Update() {
    mShader.setUniform("aPos", glm::vec3(mTransform.location, 0.0f));
    mTransform.location += mTransform.forward();
}

void Bullet::Draw() {
    mShader.use();
    glm::mat4x4 model = mTransform.GenerateModelTransform();
    mShader.setUniform("model", model);
    mShader.setUniform("view", GLShaderProgram::ViewMatrix);
    mShader.setUniform("projection", GLShaderProgram::ProjectionMatrix);
    mShader.setUniform("uColor", 0.5f);
    // mVertexArray.use();
    glDrawArrays(GL_POINTS, 0 ,1);
}
