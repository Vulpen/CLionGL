#ifndef CLIONGL_GLVERTEXARRAY_H
#define CLIONGL_GLVERTEXARRAY_H

#include <glad.h>

class GLVertexArray {
public:
    GLVertexArray();
    void Generate();
    void use();
private:
    GLuint mVAOID = 0;
};


#endif //CLIONGL_GLVERTEXARRAY_H
