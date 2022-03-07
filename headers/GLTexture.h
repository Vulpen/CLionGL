#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include "glad.h"
#include <iostream>

/**
 * Possible things to add:
 * Texture Wrap Function, Texture filtering, mipmap settings
 */
class GLTexture {
public:
    void loadTexture(const char* textureFilePath);
    void use();
private:
    int width, height, nrChannels;
    unsigned char *data;
    GLuint glTextureID;
};

#endif