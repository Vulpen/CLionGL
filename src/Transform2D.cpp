#include "Transform2D.h"

Transform2D::Transform2D() : location(glm::vec2(0, 0)), scale(glm::vec2(1, 1)), mRotationRadians(0) {

}

glm::mat4x4 Transform2D::GenerateModelTransform() {
    glm::mat4x4 model = glm::translate(
            glm::mat4(1.0f),
            glm::vec3(location.x, location.y, 0)
    )
                        * glm::rotate(glm::mat4(1.0f), mRotationRadians, glm::vec3(0.0f, 0.0f, 1.0f))
                        * glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, 1))
    ;
    return model;
}

void Transform2D::SetRotation(float value) {
    mRotationRadians = value;
}

float Transform2D::GetRotation() const {
    return mRotationRadians;
}

glm::vec2 Transform2D::forward() {
    return glm::vec2(glm::cos(mRotationRadians), glm::sin(mRotationRadians));
}

void Transform2D::operator=(const Transform2D &other) {
    location = other.location;
    mRotationRadians = other.GetRotation();
    scale = other.scale;
}
