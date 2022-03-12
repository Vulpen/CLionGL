#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <glad.h>
#include <glm.hpp>
#include <ext.hpp>
#include <string>
#include <map>

using std::string;

class GLShaderProgram {
public:
    GLShaderProgram();

    ~GLShaderProgram();

    enum ShaderType {
        VERTEX,
        FRAGMENT,
        PROGRAM
    };

    bool loadAndCompileShaders(const char *vertexFilepath, const char *fragmentFilepath);
    void use();
    void setUniform(const GLchar* name, const GLfloat value);
    void setUniform(const GLchar* name, const glm::mat4& m);
    static glm::mat4x4 ViewMatrix;
    static glm::mat4x4 ProjectionMatrix;

private:
    string fileToString(const string &filepath);
    void checkCompileErrors(GLuint shader, ShaderType type);
    GLint getUniformLocation(const GLchar* name);

    GLuint mShaderID;
    std::map<string, GLint> mUniformMap;
};

#endif