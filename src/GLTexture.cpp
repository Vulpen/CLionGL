#include "GLTexture.h"
#include "stb_image.h"

void GLTexture::loadTexture(const char *textureFilePath) {
    data = stbi_load(textureFilePath, &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Could not load texture" << std::endl;
        throw std::exception();
    }
    glGenTextures(1, &glTextureID);
    glBindTexture(GL_TEXTURE_2D, glTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

void GLTexture::use() {
    glBindTexture(GL_TEXTURE_2D, glTextureID);
}