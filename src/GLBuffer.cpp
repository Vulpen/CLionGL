#include "GLBuffer.h"

GLBuffer::GLBuffer(GLuint BufferType, GLuint DataSuggestion): mID(0), mBufferType(BufferType), mDataSuggestion(DataSuggestion) { }

GLBuffer::~GLBuffer() {
    glDeleteBuffers(1, &mID);
}

/**
 * This version of generate takes in a void pointer, which means it can take any type of buffer!
 * Should take precidence over the other function calls.
 */
void GLBuffer::Generate(const GLvoid *bufferStart, int sizeBytes) {
    if(mID != 0) {
        std::cerr << "Attempt to regenerate an existing buffer." << std::endl;
        throw std::exception();
    }

    glGenBuffers(1, &mID);
    glBindBuffer(mBufferType, mID);
    glBufferData(mBufferType, sizeBytes, bufferStart, mDataSuggestion);
}

void GLBuffer::bind() const {
    if(mID == 0) {
        std::cerr << "Attempt to use unallocated buffer." << std::endl;
        throw std::exception();
    }
    glBindBuffer(mBufferType, mID);
}

void GLBuffer::unbind() const {
    if(mID == 0) {
        std::cerr << "Attempt to use unallocated buffer." << std::endl;
        throw std::exception();
    }
    glBindBuffer(mBufferType, 0);
}


GLBuffer::GLBuffer() {}