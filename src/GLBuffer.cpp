#include "GLBuffer.h"

GLBuffer::GLBuffer(GLuint BufferType, GLuint DataSuggestion) {
    mBufferType = BufferType; mDataSuggestion = DataSuggestion;
}

void GLBuffer::Generate(const GLfloat *arrStart, int arrayLength) {
    if(mID != 0) {
        std::cerr << "Attempt to regenerate an existing buffer." << std::endl;
        throw std::exception();
    }

    glGenBuffers(1, &mID);
    glBindBuffer(mBufferType, mID);
    glBufferData(mBufferType, sizeof(GLfloat) * arrayLength, arrStart, mDataSuggestion);
}

void GLBuffer::Generate(const GLuint *arrStart, int arrayLength) {
    if(mID != 0) {
        std::cerr << "Attempt to regenerate an existing buffer." << std::endl;
        throw std::exception();
    }

    glGenBuffers(1, &mID);
    glBindBuffer(mBufferType, mID);
    glBufferData(mBufferType, sizeof(GLuint) * arrayLength, arrStart, mDataSuggestion);
}

void GLBuffer::use() {
    if(mID == 0) {
        std::cerr << "Attempt to use unallocated buffer." << std::endl;
        throw std::exception();
    }
    glBindBuffer(mBufferType, mID);
}


GLBuffer::GLBuffer() {}