#include "GLVertexArray.h"
#include <iostream>

void GLVertexArray::Generate() {
    if(mVAOID != 0) {
        std::cerr << "Attempt to recreate a vertex array which is currently unsupported" << std::endl;
        throw std::exception();
    }

    glGenVertexArrays(1, &mVAOID);
    glBindVertexArray(mVAOID);
}

void GLVertexArray::use() {
    if(mVAOID == 0) {
        std::cerr << "Attempt to use an unallocated vertex array." << std::endl;
        throw std::exception();
    }

    glBindVertexArray(mVAOID);
}

GLVertexArray::GLVertexArray(){}
