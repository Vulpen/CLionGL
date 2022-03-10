#ifndef CLIONGL_GLBUFFER_H
#define CLIONGL_GLBUFFER_H

#include <glad.h>
#include <iostream>

class GLBuffer {
public:
    GLBuffer(GLuint BufferType, GLuint DataSuggestion);
    ~GLBuffer();
    void Generate(const GLvoid* bufferStart, int sizeBytes);
    void Generate(const GLfloat* arrStart, int arrayLength);
    void Generate(const GLuint* arrStart, int arrayLength);
    void bind() const;
    void unbind() const;
private:
    GLBuffer();
    GLuint mBufferType;
    GLuint mDataSuggestion;
    GLuint mID;
};


#endif //CLIONGL_GLBUFFER_H
