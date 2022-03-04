#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <glad.h>
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

private:
    string fileToString(const string &filepath);
    void checkCompileErrors(GLuint shader, ShaderType type);

    GLuint mShaderID;
    std::map<string, GLint> mUniformMap;
};

#endif