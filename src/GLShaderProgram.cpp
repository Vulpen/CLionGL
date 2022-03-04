#include "GLShaderProgram.h"
#include <sstream>
#include <iostream>
#include <fstream>

void GLShaderProgram::use() {
    if (mShaderID > 0) {
        glUseProgram(mShaderID);
    }
}

bool GLShaderProgram::loadAndCompileShaders(const char *vsFilename, const char *fsFilename) {
    string vsString = fileToString(vsFilename);
    string fsString = fileToString(fsFilename);
    const GLchar *vsSourcePtr = vsString.c_str();
    const GLchar *fsSourcePtr = fsString.c_str();

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vs, 1, &vsSourcePtr, NULL);
    glShaderSource(fs, 1, &fsSourcePtr, NULL);

    glCompileShader(vs);
    checkCompileErrors(vs, VERTEX);
    glCompileShader(fs);
    checkCompileErrors(fs, FRAGMENT);


    mShaderID = glCreateProgram(); //Shader program is a collection of shaders
    glAttachShader(mShaderID, vs);
    glAttachShader(mShaderID, fs);
    glLinkProgram(mShaderID);

    checkCompileErrors(mShaderID, PROGRAM);


    glDeleteShader(vs); //Delete shaders because they're linked to the program
    glDeleteShader(fs);
    //End Shaders-----------

    mUniformMap.clear();
    return true;
}

void GLShaderProgram::checkCompileErrors(GLuint shader, ShaderType type) {
    int status = 0;

    if (type == PROGRAM) {
        glGetProgramiv(mShaderID, GL_LINK_STATUS, &status);
        if (status == GL_FALSE) {
            GLint length = 0;
            glGetProgramiv(mShaderID, GL_INFO_LOG_LENGTH, &length);

            string errorLog(length, ' ');
            glGetProgramInfoLog(mShaderID, length, &length, &errorLog[0]);
            std::cerr << "Error! Shader program failed on link." << errorLog << std::endl;
        }
    } else {
        //Vertex or Fragment
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            GLint length = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

            string errorLog(length, ' ');
            glGetShaderInfoLog(shader, length, &length, &errorLog[0]);
            std::cerr << "Error! Shader program failed to compile." << errorLog << std::endl;
        }
    }
}

string GLShaderProgram::fileToString(const string &filename) {
    std::stringstream ss;
    std::ifstream file;

    try {
        file.open(filename, std::ios::in);
        if (!file.fail()) {
            ss << file.rdbuf();
        }

        file.close();
    }
    catch (std::exception e) {
        std::cerr << "Could not open shader file" << std::endl;
    }

    return ss.str();
}