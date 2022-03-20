#ifndef CLIONGL_TRANSFORM2D_H
#define CLIONGL_TRANSFORM2D_H

#include <ext.hpp>
#include <glm.hpp>

class Transform2D {
public:
    Transform2D();
    glm::mat4x4 GenerateModelTransform();
    void SetRotation(float value);
    float GetRotation() const;
    void operator = (const Transform2D& other);
    glm::vec2 forward();
    glm::vec2 location;
    glm::vec2 scale;
private:
    float mRotationRadians;
};


#endif //CLIONGL_TRANSFORM2D_H
