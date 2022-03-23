#ifndef CLIONGL_BULLET_H
#define CLIONGL_BULLET_H

#include "GLShaderProgram.h"
#include "Transform2D.h"

class Bullet {
public:
    Bullet();
    void Update();
    void Draw();

private:
    float mRadius;
    GLShaderProgram mShader;
    Transform2D mTransform;
};


#endif //CLIONGL_BULLET_H
