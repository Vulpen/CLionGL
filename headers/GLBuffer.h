#ifndef CLIONGL_GLBUFFER_H
#define CLIONGL_GLBUFFER_H

#include <glad.h>
#include <iostream>

class GLBuffer {
public:
    GLBuffer(GLuint BufferType, GLuint DataSuggestion);
    void Generate(const GLfloat* arrStart, int arrayLength);
    void Generate(const GLuint* arrStart, int arrayLength);
    void use();
private:
    GLBuffer();
    GLuint mBufferType;
    GLuint mDataSuggestion;
    GLuint mID;
};


#endif //CLIONGL_GLBUFFER_H
